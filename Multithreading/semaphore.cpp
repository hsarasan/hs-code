#include <iostream>
#include <vector>
#include <thread>
#include <syncstream>
#include <mutex>

std::counting_semaphore<4> sem(3);
std::mutex m;
void thread_fn(int x){
    sem.acquire();
    std::unique_lock<std::mutex> l(m);
    std::cout<<"starting "<<x<<std::endl;
    l.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::unique_lock<std::mutex> l2(m);
    std::cout<<"Exiting "<<x<<std::endl;
    l2.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    sem.release();
}

int main(){
    std::vector<std::jthread> v;
    for (int i=0;i<10;++i){
        v.emplace_back(thread_fn,i);
    }
    std::cout<<"Exiting main thread.."<<std::endl;
    return 0;
}