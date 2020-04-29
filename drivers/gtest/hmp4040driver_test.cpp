#include <gtest/gtest.h>
#include <memory>
#include <hmp4040_driver.h>
#include "mocktcpsocket.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

const QString address = "192.168.1.105";
const int port = 5025;
const int threadDelay = 30;

TEST(HMP4040Driver, testOpen)
{
    auto socket = std::make_shared<MockTcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket);

    EXPECT_CALL(*socket, connect(address, port))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*socket, close()).Times(1);

    EXPECT_TRUE(driver->open(address, port));
}

TEST(HMP4040Driver, testSetOutput)
{
    auto socket = std::make_shared<MockTcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket);
    const int channel = 1;
    EXPECT_CALL(*socket, connect(address, port))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*socket, read(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, write(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, close()).Times(1);

    driver->open(address, port);
    for (const auto &enable : {false, true}) {
        EXPECT_CALL(*socket, write(QString("Output:State %0\n").arg(enable)))
                .Times(1)
                .WillOnce(Return(true));
        driver->setOutput(enable, channel);
    }
    EXPECT_FALSE(driver->wait(threadDelay));
}

TEST(HMP4040Driver, testSetVoltage)
{
    auto socket = std::make_shared<MockTcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket);
    const float volt = 18.0;
    const int channel = 1;
    EXPECT_CALL(*socket, connect(address, port))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*socket, read(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, write(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, close()).Times(1);

    EXPECT_CALL(*socket, write(QString("Voltage %0\n").arg(volt)))
            .Times(1)
            .WillOnce(Return(true));
    driver->open(address, port);
    driver->setVoltage(volt, channel);
    EXPECT_FALSE(driver->wait(threadDelay));
}

TEST(HMP4040Driver, testSetCurrent)
{
    auto socket = std::make_shared<MockTcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket);
    const float curr = 2.0;
    const int channel = 1;
    EXPECT_CALL(*socket, connect(address, port))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*socket, read(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, write(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, close()).Times(1);

    EXPECT_CALL(*socket, write(QString("Current %0\n").arg(curr)))
            .Times(1)
            .WillOnce(Return(true));
    driver->open(address, port);
    driver->setCurrent(curr, channel);
    EXPECT_FALSE(driver->wait(threadDelay));
}

TEST(HMP4040Driver, testVoltage)
{
    auto socket = std::make_shared<MockTcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket);
    const float volt = 18.0;
    const int channel = 1;
    EXPECT_CALL(*socket, connect(address, port))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*socket, write(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, close()).Times(1);

    EXPECT_CALL(*socket, read(_))
            .Times(AtLeast(1))
            .WillRepeatedly([&](QString &message){
        message = QString("%0\n").arg(volt);
        return true;
    });
    driver->open(address, port);
    EXPECT_FALSE(driver->wait(threadDelay));
    EXPECT_EQ(driver->voltage(channel), volt);
}

TEST(HMP4040Driver, testCurrent)
{
    auto socket = std::make_shared<MockTcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket);
    const float curr = 2.0;
    const int channel = 1;
    EXPECT_CALL(*socket, connect(address, port))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*socket, write(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*socket, close()).Times(1);

    EXPECT_CALL(*socket, read(_))
            .Times(AtLeast(1))
            .WillRepeatedly([&](QString &message){
        message = QString("%0\n").arg(curr);
        return true;
    });
    driver->open(address, port);
    EXPECT_FALSE(driver->wait(threadDelay));
    EXPECT_EQ(driver->current(channel), curr);
}
