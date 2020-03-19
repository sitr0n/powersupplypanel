#pragma once
#include <vector>

class PSUInterface
{
public:
    virtual ~PSUInterface() { }
    virtual std::vector<int> channels() = 0;

    virtual void setOutput(bool enable, int channel = 1) = 0;
    virtual void setVoltage(float voltage, int channel = 1) = 0;
    virtual void setCurrent(float current, int channel = 1) = 0;

    virtual float voltage(int channel = 1) = 0;
    virtual float current(int channel = 1) = 0;

};
