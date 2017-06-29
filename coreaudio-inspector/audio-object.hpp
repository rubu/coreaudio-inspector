#pragma once

#include "audio-object-property.hpp"
#include "os-status-exception.hpp"

class CAudioObject
{
public:
    CAudioObject(int nId);
    
    int GetId();
    
    template<typename T>
    UInt32 GetPropertySize(const T& AudioObjectProperty)
    {
        UInt32 nPropertySize;
        CHECK_OSSTATUS(AudioObjectGetPropertyDataSize(m_nId, &AudioObjectProperty, 0, NULL, &nPropertySize));
        return nPropertySize;
    }

    template<typename T>
    void GetPropertyData(const T& AudioObjectProperty, UInt32& nPropertySize, void* pPropertyData)
    {
        CHECK_OSSTATUS(AudioObjectGetPropertyData(m_nId, &AudioObjectProperty, 0, NULL, &nPropertySize, pPropertyData));
    }


protected:
    int m_nId;
};