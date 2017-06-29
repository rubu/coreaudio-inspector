#include "os-status-exception.hpp"

std::ostream& operator<<(std::ostream& OutputStream, const COSStatusException& Exception)
{
    OutputStream << "!!! invalid OSStatus return code 0x" << std::hex << Exception.m_nOSStatus << " at " << Exception.m_pFile << "(" << Exception.m_nLine << ")";
    return OutputStream;
}

COSStatusException::COSStatusException(OSStatus nOSStatus, int nLine, const char* pFile) : m_nOSStatus(nOSStatus),
    m_nLine(nLine),
    m_pFile(pFile)
{
}



