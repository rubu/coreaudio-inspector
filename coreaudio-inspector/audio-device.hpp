#pragma once

#include "audio-object.hpp"

#include <string>
#include <ostream>

class CAudioDevice : public CAudioObject
{
    friend std::ostream& operator<<(std::ostream& OutputStream, const CAudioDevice& AudioDevice);
public:
    CAudioDevice(int nId);
    
    const std::string& GetName();
    
private:
    std::string m_sName;
};

std::ostream& operator<<(std::ostream& OutputStream, const CAudioDevice& AudioDevice);
