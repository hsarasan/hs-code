#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <functional>
#include <mutex>
#include <atomic>

using namespace std::literals;

int value{0};
std::atomic<int> V{0};
std::mutex m;

struct Spinlock{
    std::atomic_flag flag{false};
    public:
        void lock(){ while(flag.test_and_set());}
        void unlock() { flag.clear();}
};
Spinlock s;

void increment1(){
    for (int i=0;i<1000;++i){
        std::lock_guard<std::mutex> l(m);
        value++;
    }
}

void increment2(){
    for (int i=0;i<1000;++i){
        s.lock();
        value++;
        s.unlock();
    }
}

void increment3(){
    for (int i=0;i<1000;++i){
       V++;
    }
}


int main(int argc, char * argv[]){

    if (argc<2){
        std::cerr<<"Usage:" << argv[0]<<" <NUM THREADS>"<<std::endl;
        return 1;
    }

    int NUM_THREADS = std::stoi(argv[1]);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (int i=0;i<NUM_THREADS;++i)
        threads.emplace_back(increment1);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    assert(value=NUM_THREADS*1000);
    std::cout<<"TimeTaken with Mx="<<ms_int.count()<<std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    threads.clear();
    value=0;
    for (int i=0;i<NUM_THREADS;++i)
        threads.emplace_back(increment2);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    t2 = std::chrono::high_resolution_clock::now();
    ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    assert(value=NUM_THREADS*1000);
    std::cout<<"TimeTaken with SpinLock="<<ms_int.count()<<std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    threads.clear();
    for (int i=0;i<NUM_THREADS;++i)
        threads.emplace_back(increment3);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    t2 = std::chrono::high_resolution_clock::now();
    ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    assert(V.load()==NUM_THREADS*1000);
    std::cout<<"TimeTaken with Atomic="<<ms_int.count()<<std::endl;

}