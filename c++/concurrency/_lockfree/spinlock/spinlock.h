#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_


#include <thread>
#include <atomic>

namespace HS{

    class SpinLock{

    public:
        void lock(){
            while(!flag.test_and_set()){}
        }
        void unlock(){
            flag.clear();
        }
        SpinLock():flag(ATOMIC_FLAG_INIT){}

    private:
        std::atomic_flag flag;

};

};

#endif