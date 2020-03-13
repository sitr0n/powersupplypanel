#pragma once
#include <vector>

class PSUInterface
{
public:
    PSUInterface() : m_channels(std::vector<int>{1}) { }
    virtual ~PSUInterface() { }
    std::vector<int> channels() const { return m_channels; }

    virtual void setOutput(bool enable, int channel = 1) = 0;
    virtual void setVoltage(float voltage, int channel = 1) = 0;
    virtual void setCurrent(float current, int channel = 1) = 0;

    virtual float voltage(int channel = 1) = 0;
    virtual float current(int channel = 1) = 0;

protected:
    std::vector<int> m_channels;
};
