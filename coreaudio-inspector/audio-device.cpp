#include "audio-device.hpp"

CAudioDevice::CAudioDevice(int nId) : CAudioObject(nId)
{
    const CAudioDeviceNameProperty AudioDeviceNameProperty;
    CFStringRef sNamePropertyValue;
    UInt32 nNamePropertySize = sizeof(sNamePropertyValue);
    GetPropertyData(AudioDeviceNameProperty, nNamePropertySize, &sNamePropertyValue);
    auto* pNamePropertyValue = CFStringGetCStringPtr(sNamePropertyValue,kCFStringEncodingUTF8);
    if (pNamePropertyValue)
    {
        m_sName = pNamePropertyValue;
    }
}

const std::string& CAudioDevice::GetName()
{
    return m_sName;
}

std::ostream& operator<<(std::ostream& OutputStream, const CAudioDevice& AudioDevice)
{
    OutputStream << '"'<< AudioDevice.m_sName << "\"(" << AudioDevice.m_nId << ')';
    return OutputStream;
}