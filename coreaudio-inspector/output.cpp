#include "output.hpp"

#include <chrono>
#include <iomanip>

COutput::CLine::CLine(std::recursive_mutex& Mutex) : m_Mutex(Mutex),
    m_Lock(m_Mutex)
{
    auto Now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "[" << std::put_time(std::localtime(&Now), "%Y-%m-%d %X") << "]: ";
}

COutput::CLine::CLine(const CLine& Line) : m_Mutex(Line.m_Mutex),
    m_Lock(m_Mutex)
{
    
}

COutput::CLine::~CLine()
{
    std::cout << "\n";
}