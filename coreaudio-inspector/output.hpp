#pragma once

#include <mutex>
#include <iostream>

class COutput
{
public:
    class CLine
    {
    public:
        CLine(std::recursive_mutex& Mutex);
        CLine(const CLine& Line);
        ~CLine();
        
        template<typename T>
        CLine& operator<<(const T& Value)
        {
            std::cout << Value;
            return *this;
        }

    private:
        std::recursive_mutex& m_Mutex;
        std::lock_guard<std::recursive_mutex> m_Lock;
    };
    
    template<typename T>
    CLine operator<<(const T& Value)
    {
        CLine Line(m_Mutex);
        Line << Value;
        return Line;
    }

private:
    std::recursive_mutex m_Mutex;
};

static COutput g_Output;
