#pragma once
#include "tcpsocketinterface.h"
#include <QtNetwork>
#include <vector>
#include <memory>

class TcpSocket : public TcpSocketInterface
{
public:
    TcpSocket();
    ~TcpSocket() = default;
    bool connect(const QString &address, int port);
    void close();

    bool write(const QString &message);
    bool read(QString &message);

private:
    QTcpSocket m_socket;
    std::unique_ptr<QDataStream> m_stream;
    std::vector<int> m_byteRange;
    const int TIMEOUT = 3000;
};
