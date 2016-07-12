#include "common/FSSpinlock.h"
using namespace freestick;
void FSSpinLock::lock()
{
    while(locked.test_and_set(std::memory_order_acquire)){;}
}
bool FSSpinLock::try_lock()
{
    return !locked.test_and_set(std::memory_order_acquire);
}

void FSSpinLock::unlock()
{
    locked.clear(std::memory_order_release);
}
