#pragma once

#include "audio-object.hpp"
#include "audio-device.hpp"

#include <mutex>
#include <map>

class CAudioObjectManager
{
public:
    CAudioObjectManager();
    
public:
    void GetAudioDevices();
    void GetDefaultInputDevice();
    void GetDefaultOutputDevice();

private:
    std::recursive_mutex m_Mutex;
    CAudioObject m_SystemObject;
    std::map<int, CAudioDevice> m_AudioDevices;
    AudioDeviceID m_nDefaultInputDevice;
    AudioDeviceID m_nDefaultOutputDevice;

public:
    static const CAudioDevicesProperty s_AudioDevicesProperty;
    static const CDefaultInputDeviceProperty s_DefaultInputDeviceProperty;
    static const CDefaultOutputDeviceProperty s_DefaultOutputDeviceProperty;
};
