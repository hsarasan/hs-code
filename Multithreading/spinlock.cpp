#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>

struct spinlock{
    std::atomic_flag flag;
    public:
        void lock(){
            while(flag.test_and_set());
        }
        void unlock(){
            flag.clear();
        }
};

void print(int start, int end, spinlock & lock){
    for (int i=start; i<end+1; ++i){
        lock.lock();
        std::cout<<"From Thread "<<std::this_thread::get_id()<<"=>"<<i<<std::endl;
        lock.unlock();
    }
}

int main(){
    std::vector<std::thread> v;
    spinlock sp;
    for (int i=0;i<5;++i){
        v.emplace_back(print, i*4, i*4+3, std::ref(sp));
    }
    std::for_each(v.begin(), v.end(),  std::mem_fn(&std::thread::join));    
}