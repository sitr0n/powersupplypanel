#include "tcpsocket.h"

TcpSocket::TcpSocket()
    : m_stream(new QDataStream(&m_socket))
    , m_byteRange({7, 6, 5, 4, 3, 2})
{
    m_stream->setVersion(QDataStream::Qt_4_0);
}

bool TcpSocket::connect(const QString &address, int port)
{
    m_socket.connectToHost(address, port);
    return m_socket.waitForConnected(TIMEOUT);
}

void TcpSocket::close()
{
    m_socket.close();
}

bool TcpSocket::write(const QString &message)
{
    return m_socket.write(message.toStdString().c_str()) == message.size();
}

bool TcpSocket::read(QString &response)
{
    if (!m_socket.waitForReadyRead(TIMEOUT)) {
        return false;
    }

    for (const auto &size : m_byteRange) {
        auto buffer = new char[size + 1];
        buffer[size] = '\0';

        m_stream->startTransaction();
        m_stream->readRawData(buffer, size);
        response = QString(buffer);
        delete[] buffer;

        if (m_stream->commitTransaction()) {
            return true;
        }
    }
    response.clear();
    return false;
}
