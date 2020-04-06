#include "common/FSSpinlock.h"
using namespace freestick;
void FSSpinLock::lock()
{
    while(m_locked.test_and_set(std::memory_order_acquire)){;}
}
bool FSSpinLock::try_lock()
{
    return !m_locked.test_and_set(std::memory_order_acquire);
}

void FSSpinLock::unlock()
{
    m_locked.clear(std::memory_order_release);
}
