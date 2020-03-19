#pragma once
//#include <psuinterface.h>
#include "../psuinterface.h"
#include <gmock/gmock.h>

class MockPSUInterface : public PSUInterface
{
public:
    ~MockPSUInterface() { }
    MOCK_METHOD0(channels, std::vector<int>());
    MOCK_METHOD2(setOutput, void(bool enable, int channel));
    MOCK_METHOD2(setVoltage, void(float voltage, int channel));
    MOCK_METHOD2(setCurrent, void(float current, int channel));
    MOCK_METHOD1(voltage, float(int channel));
    MOCK_METHOD1(current, float(int channel));
};
