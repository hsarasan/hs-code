#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

struct spinLock{
    atomic_flag b{ATOMIC_FLAG_INIT};
    void lock(){
        while (b.test_and_set(memory_order_acquire)){}
    }
    void unlock(){
        b.clear(memory_order_release);
    }
};

int main(){
    return 0;
}