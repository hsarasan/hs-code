#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

struct SpinLock{

    std::atomic_flag flag=ATOMIC_FLAG_INIT;
    void lock(){
        while(flag.test_and_set(memory_order_acquire)){}
    }
    void unlock(){
        flag.clear(memory_order_relaxed);
    }
};
int g{0};
SpinLock spin;
void increment(){
    for (int i=0;i<100000;++i){
        spin.lock();
        g++;
        spin.unlock();
    }
}

int main(){
    vector<thread> threads;
    for (int i=0;i<4;++i ){
        threads.emplace_back(increment);
    }
    for (auto &thr: threads){
        thr.join();
    }
    cout<<g<<endl;
}