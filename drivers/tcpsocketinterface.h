#pragma once
#include <QString>

class TcpSocketInterface
{
public:
    virtual ~TcpSocketInterface() {}
    virtual bool connect(const QString &address, int port) = 0;
    virtual void close() = 0;

    virtual bool write(const QString &message) = 0;
    virtual bool read(QString &message) = 0;
};
