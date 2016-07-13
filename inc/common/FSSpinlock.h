#ifndef FSSPINLOCK_H
#define FSSPINLOCK_H

#include <atomic>
namespace  freestick
{
    class FSSpinLock
    {
    public:
       explicit FSSpinLock()
       {
            //sets the atomic_flag to false before use
            //This is a work around for VS 2013 not supporting
            //std::atomic_flag locked = ATOMIC_FLAG_INIT
            //Once VS 2013 is droped this code should be changed back
            locked.clear();
        }
        void lock();
        bool try_lock();
        void unlock();
     private:
        std::atomic_flag locked ;
    };
}
#endif // FSSPINLOCK_H
