#pragma once
#include <tcpsocketinterface.h>
#include <gmock/gmock.h>

class MockTcpSocket : public TcpSocketInterface
{
public:
    ~MockTcpSocket() { }
    MOCK_METHOD2(connect, bool(const QString &address, int port));
    MOCK_METHOD0(close, void());
    MOCK_METHOD1(write, bool(const QString &message));
    MOCK_METHOD1(read, bool(QString &message));
};
