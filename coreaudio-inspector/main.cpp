#include "audio-object-manager.hpp"
#include "output.hpp"

#include <cstdlib>
#include <condition_variable>
#include <mutex>

std::mutex Mutex;
std::condition_variable ConditionVariable;

int main(int argc, const char * argv[])
{
    try
    {
        CAudioObjectManager AudioObjectManager;
        std::unique_lock<std::mutex> Lock(Mutex);
        ConditionVariable.wait(Lock);
        return EXIT_SUCCESS;
    }
    catch(COSStatusException& Exception)
    {
        g_Output << Exception;
        return EXIT_FAILURE;
    }
    catch(std::exception& Exception)
    {
        return EXIT_FAILURE;
    }
}
