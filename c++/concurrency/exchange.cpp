#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <vector>

std::mutex m;
std::atomic<int> counter;
std::atomic<int> Value{0};
int MAX_VAL=5;
auto func = [](){

    int next{0};
    while(next<MAX_VAL+1)
    {   
        {
            std::lock_guard<std::mutex> lock(m);
            std::cout<<"From Id "<<std::this_thread::get_id()<<" trying to write "<<next<<std::endl;
        }
        int current = Value.exchange(next);
        counter++;
        next=current+1;
    }
};

int main(){

    std::vector<std::thread> threads;
    for (int i=0; i<5; i++)
    {
        threads.emplace_back(std::thread(func) );
    }
    for (auto & thr: threads)
    {
        thr.join();
    }
    std::cout<<"No of tries "<<counter<<std::endl;
    std::cout<<Value.load()<<std::endl;
    std::cout<<Value.is_lock_free()<<std::endl;
}