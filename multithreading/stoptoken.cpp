#include <iostream>
#include <thread>

struct Experiment{
    void * operator()(){
        return this;
    }
};

void thread_fn(std::stop_token token){
    while(!token.stop_requested()){
        std::cout<<"From thread_fn"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout<<"exiting..."<<std::endl;

}

int main(){
    std::stop_token token;
    auto tid=std::jthread(thread_fn);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    tid.request_stop();
    std::this_thread::sleep_for(std::chrono::seconds(5));
   return 0;
}