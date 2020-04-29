#include "hmp4040_driver.h"
#include <QMutexLocker>

HMP4040Driver::HMP4040Driver(std::shared_ptr<TcpSocketInterface> socket, QObject *parent) noexcept
    : QThread(parent)
    , m_socket(socket)
    , m_getMissed(false)
{
    m_channels = std::vector<int>{1, 2, 3, 4};
}

HMP4040Driver::~HMP4040Driver()
{
    if (!exitEventLoop()) {
        emit error("HMP4040Driver::~HMP4040Driver() : Failed to stop event loop");
    }
}

std::vector<int> HMP4040Driver::channels()
{
    return m_channels;
}

bool HMP4040Driver::open(const QString &address, const int port)
{
    if (!exitEventLoop()) {
        emit error(QString("HMP4040Driver::open(%0, %1) : Failed to stop event loop").arg(address).arg(port));
        return false;
    }
    m_address = address;
    m_port = port;
    return startEventLoop();
}

void HMP4040Driver::setOutput(const bool enable, const int channel)
{
    enqueue([&, enable, channel]{
        return post("Instrument", QString("Output%0").arg(channel)) && post("Output:State", enable);
    });
}

void HMP4040Driver::setVoltage(const float voltage, const int channel)
{
    enqueue([&, voltage, channel]{
        return post("Instrument", QString("Output%0").arg(channel)) && post("Voltage", voltage);
    });
}

void HMP4040Driver::setCurrent(const float current, const int channel)
{
    enqueue([&, current, channel]{
        return post("Instrument", QString("Output%0").arg(channel)) && post("Current", current);
    });
}

float HMP4040Driver::voltage(const int channel)
{
    QMutexLocker lock(&m_mutex);
    return m_voltage[channel];
}

float HMP4040Driver::current(const int channel)
{
    QMutexLocker lock(&m_mutex);
    return m_current[channel];
}

void HMP4040Driver::run()
{
    QMutexLocker lock(&m_mutex);
    if (!m_socket->connect(m_address, m_port)) {
        return;
    }
    while (!m_events.empty()) {
        auto event = m_events.dequeue();
        m_mutex.unlock();
        auto delivered = event();
        m_mutex.lock();
        if (!delivered) {
            m_events.enqueue(event);
        }
    }
    m_socket->close();
}

bool HMP4040Driver::startEventLoop()
{
    for (const auto &channel : m_channels) {
        setup(channel);
    }
    start();
    return isRunning();
}

bool HMP4040Driver::exitEventLoop()
{
    m_mutex.lock();
    m_events.clear();
    m_mutex.unlock();
    return wait();
}

void HMP4040Driver::setup(int channel)
{
    enqueue([&, channel]{
        if (!post("Instrument", QString("Output%0").arg(channel))) {
            QMutexLocker lock(&m_mutex);
            return m_events.empty();
        }
        auto value = get("Measure:Voltage");
        QMutexLocker lock(&m_mutex);
        if (!value.isEmpty()) {
            m_voltage[channel] = value.toDouble();
        }
        return m_events.empty();
    });
    enqueue([&, channel]{
        if (!post("Instrument", QString("Output%0").arg(channel))) {
            QMutexLocker lock(&m_mutex);
            return m_events.empty();
        }
        auto value = get("Measure:Current");
        QMutexLocker lock(&m_mutex);
        if (!value.isEmpty()) {
            m_current[channel] = value.toDouble();
        }
        return m_events.empty();
    });
}

template <class Type>
bool HMP4040Driver::post(const QString &resource, Type value)
{
    return m_socket->write(QString("%0 %1\n").arg(resource).arg(value));
}

QString HMP4040Driver::get(const QString &resource)
{
    QString reply;
    if (m_getMissed) {
        QThread::msleep(100);
        m_socket->read(reply);
        m_getMissed = false;
    }
    if (!m_socket->write(QString("%1?\n").arg(resource))) {
        emit error(QString("HMP4040Driver::get(%0) : Failed to write").arg(resource));
        return reply;
    }
    if (!m_socket->read(reply)) {
        emit error(QString("HMP4040Driver::get(%0) : Failed to read").arg(resource));
        m_getMissed = true;
    }
    return reply.remove('\n');
}

void HMP4040Driver::enqueue(std::function<bool()> event)
{
    QMutexLocker lock(&m_mutex);
    m_events.enqueue(event);
}
