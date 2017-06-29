#include "audio-object.hpp"

CAudioObject::CAudioObject(int nId) : m_nId(nId)
{
}

int CAudioObject::GetId()
{
    return m_nId;
}