#pragma once
#include "psuinterface.h"
#include "tcpsocketinterface.h"
#include <QThread>
#include <QtNetwork>
#include <QMutex>
#include <QQueue>
#include <QMap>
#include <memory>
#include <functional>

class HMP4040Driver : public QThread, public PSUInterface
{
    Q_OBJECT
public:
    explicit HMP4040Driver(TcpSocketInterface *socket, QObject *parent = nullptr) noexcept;
    ~HMP4040Driver() override;

    bool open(const QString &address, const int port);
    void setOutput(const bool enable, const int channel);
    void setVoltage(const float voltage, const int channel);
    void setCurrent(const float current, const int channel);
    float voltage(const int channel);
    float current(const int channel);

signals:
    void error(const QString &message);

protected:
    virtual void run() override;
    bool startEventLoop();
    bool exitEventLoop();
    void setup(int channel);

    template <class Type>
    bool post(const QString &resource, Type value);
    QString get(const QString &resource);
    void enqueue(std::function<bool()> event);
    using QThread::start;

private:
    TcpSocketInterface *m_socket;
    QMap<int, double> m_voltage;
    QMap<int, double> m_current;

    QQueue<std::function<bool()>> m_events;
    QMutex m_mutex;
};
