#pragma once

#include <CoreAudio/AudioHardware.h>

template<AudioObjectPropertySelector Selector, AudioObjectPropertyScope Scope, AudioObjectPropertyElement Element>
class CAudioObjectProperty
{
public:
    CAudioObjectProperty() : m_AudioObjectPropertyAddress{Selector, Scope, Element}
    {
    }
    
    const AudioObjectPropertyAddress* operator&() const
    {
        return &m_AudioObjectPropertyAddress;
    }

    bool operator==(const AudioObjectPropertyAddress& AudioObjectProperty) const
    {
        return AudioObjectProperty.mElement == m_AudioObjectPropertyAddress.mElement &&
        AudioObjectProperty.mScope == m_AudioObjectPropertyAddress.mScope &&
        AudioObjectProperty.mSelector == m_AudioObjectPropertyAddress.mSelector;
    }

private:
    AudioObjectPropertyAddress m_AudioObjectPropertyAddress;
};

typedef CAudioObjectProperty<kAudioHardwarePropertyDevices, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster> CAudioDevicesProperty;
typedef CAudioObjectProperty<kAudioObjectPropertyName, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster> CAudioDeviceNameProperty;
typedef CAudioObjectProperty<kAudioHardwarePropertyDefaultInputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster> CDefaultInputDeviceProperty;
typedef CAudioObjectProperty<kAudioHardwarePropertyDefaultOutputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster> CDefaultOutputDeviceProperty;
