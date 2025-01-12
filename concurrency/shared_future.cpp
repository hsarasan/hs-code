#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <algorithm>

std::mutex mx;

int getToken(){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 42;
}

void process(std::shared_future<int> sf){
    int token=sf.get();
    std::unique_lock<std::mutex> ul(mx);
    std::cout<<"Got Token "<<std::this_thread::get_id()<<std::endl;
    ul.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
int main(){
    auto fut=std::async(getToken);
    std::shared_future<int> sf(std::move(fut));
    std::vector<std::thread> threads;
    for (int i=0;i<5;++i)
        threads.emplace_back(process,sf);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    std::cout<<"exiting..."<<std::endl;
}