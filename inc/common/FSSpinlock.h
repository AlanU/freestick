#ifndef FSSPINLOCK_H
#define FSSPINLOCK_H

#include <atomic>
namespace  freestick
{
    class FSSpinLock
    {
    public:
        void lock();
        bool try_lock();
        void unlock();
     private:
        std::atomic_flag locked = ATOMIC_FLAG_INIT;
    };
}
#endif // FSSPINLOCK_H
