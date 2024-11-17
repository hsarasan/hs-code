#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>

using namespace std;

std::atomic<bool> ready = false;
int value=0;

void producer(){
    value=42;
    ready.store(true,std::memory_order_release);
}
void consumer(){
    while(!ready.load(std::memory_order_acquire)){}
    assert(value==42);
}

int main(){
    auto t1 = std::thread(producer);
    auto t2 = std::thread(consumer);
    t1.join();
    t2.join();
    return 0;
}