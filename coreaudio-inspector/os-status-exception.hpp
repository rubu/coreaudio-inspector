#pragma once

#include <MacTypes.h>

#include <iostream>
class COSStatusException
{
    friend std::ostream& operator<<(std::ostream&, const COSStatusException& Exception);
public:
    COSStatusException(OSStatus nOSStatus, int nLine, const char* pFile);
    
private:
    const OSStatus m_nOSStatus;
    const int m_nLine;
    const char* m_pFile;
};

std::ostream& operator<<(std::ostream& OutputStream, const COSStatusException& Exception);

#define CHECK_OSSTATUS(x) { const auto nOSStatus = (x); if (nOSStatus != noErr) throw COSStatusException(nOSStatus, __LINE__, __BASE_FILE__); }