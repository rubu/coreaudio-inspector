#include "audio-object-manager.hpp"
#include "os-status-exception.hpp"
#include "output.hpp"

#include <type_traits>
#include <vector>

OSStatus PropertyChangeCallback(AudioObjectID nAudioObjectId, UInt32 nNumberAddresses, const AudioObjectPropertyAddress* pAddresses, void* pClientData)
{
    CAudioObjectManager* pAudioObjectManager = reinterpret_cast<CAudioObjectManager*>(pClientData);
    if (pAudioObjectManager && nNumberAddresses)
    {
        for(UInt32 nAddressIndex = 0; nAddressIndex < nNumberAddresses; ++nAddressIndex)
        {
            if (CAudioObjectManager::s_AudioDevicesProperty == pAddresses[nAddressIndex])
            {
                pAudioObjectManager->GetAudioDevices();
            }
            else if (CAudioObjectManager::s_DefaultInputDeviceProperty == pAddresses[nAddressIndex])
            {
                pAudioObjectManager->GetDefaultInputDevice();
            }
            else if (CAudioObjectManager::s_DefaultOutputDeviceProperty == pAddresses[nAddressIndex])
            {
                pAudioObjectManager->GetDefaultOutputDevice();
            }
        }
    }
    return noErr;
}

const CAudioDevicesProperty CAudioObjectManager::s_AudioDevicesProperty;
const CDefaultInputDeviceProperty CAudioObjectManager::s_DefaultInputDeviceProperty;
const CDefaultOutputDeviceProperty CAudioObjectManager::s_DefaultOutputDeviceProperty;

CAudioObjectManager::CAudioObjectManager() : m_SystemObject(kAudioObjectSystemObject)
{
    std::lock_guard<std::recursive_mutex> MutexLock(m_Mutex);
    AudioObjectAddPropertyListener(kAudioObjectSystemObject, &s_AudioDevicesProperty, PropertyChangeCallback, this);
    AudioObjectAddPropertyListener(kAudioObjectSystemObject, &s_DefaultInputDeviceProperty, PropertyChangeCallback, this);
    AudioObjectAddPropertyListener(kAudioObjectSystemObject, &s_DefaultOutputDeviceProperty, PropertyChangeCallback, this);
    GetAudioDevices();
    GetDefaultInputDevice();
    GetDefaultOutputDevice();
}

void CAudioObjectManager::GetAudioDevices()
{
    auto nAudioDevicesPropertySize = m_SystemObject.GetPropertySize(s_AudioDevicesProperty);
    const auto nAudioDeviceCount = nAudioDevicesPropertySize / sizeof(AudioDeviceID);
    std::vector<AudioDeviceID> AudioDeviceIds(nAudioDeviceCount);
    m_SystemObject.GetPropertyData(s_AudioDevicesProperty, nAudioDevicesPropertySize, AudioDeviceIds.data());
    for (auto AudioDeviceIterator = m_AudioDevices.begin(); AudioDeviceIterator != m_AudioDevices.end();)
    {
        if (std::find(AudioDeviceIds.begin(), AudioDeviceIds.end(), AudioDeviceIterator->first) == AudioDeviceIds.end())
        {
            g_Output << "device " << AudioDeviceIterator->second << " was removed";
            AudioDeviceIterator = m_AudioDevices.erase(AudioDeviceIterator);
        }
        else
        {
            ++AudioDeviceIterator;
        }
    }
    for (const auto& nAudioDeviceId : AudioDeviceIds)
    {
        CAudioDevice AudioDevice(nAudioDeviceId);
        auto AudioDeviceIterator = m_AudioDevices.find(nAudioDeviceId);
        if (AudioDeviceIterator == m_AudioDevices.end())
        {
            AudioDeviceIterator = m_AudioDevices.emplace(nAudioDeviceId, nAudioDeviceId).first;
            g_Output << "device " << AudioDeviceIterator->second << " was added";
        }
        else if (AudioDevice.GetName() != AudioDeviceIterator->second.GetName())
        {
            g_Output << "!!! device " << AudioDevice.GetName() << " changed id from " << AudioDeviceIterator->second.GetId() << " to " << AudioDevice.GetId() << " without being removed";
        }
    }
}

void CAudioObjectManager::GetDefaultInputDevice()
{
    std::lock_guard<std::recursive_mutex> MutexLock(m_Mutex);
    UInt32 nAudioDeviceIdSize = sizeof(AudioDeviceID);
    m_SystemObject.GetPropertyData(s_DefaultInputDeviceProperty, nAudioDeviceIdSize, &m_nDefaultInputDevice);
    auto DefaultInputDevice = m_AudioDevices.find(m_nDefaultInputDevice);
    if (DefaultInputDevice != m_AudioDevices.end())
    {
        g_Output << "default input device is " << DefaultInputDevice->second;
    }
    else
    {
        g_Output << "!!! default input device changed to " << m_nDefaultInputDevice << " which is not in the device list";
    }
}

void CAudioObjectManager::GetDefaultOutputDevice()
{
    std::lock_guard<std::recursive_mutex> MutexLock(m_Mutex);
    UInt32 nAudioDeviceIdSize = sizeof(AudioDeviceID);
    m_SystemObject.GetPropertyData(s_DefaultOutputDeviceProperty, nAudioDeviceIdSize, &m_nDefaultOutputDevice);
    auto DefaultOutputDevice = m_AudioDevices.find(m_nDefaultOutputDevice);
    if (DefaultOutputDevice != m_AudioDevices.end())
    {
        g_Output << "default output device is " << DefaultOutputDevice->second;
    }
    else
    {
        g_Output << "!!! default output device changed to " << m_nDefaultOutputDevice << " which is not in the device list";
    }
}