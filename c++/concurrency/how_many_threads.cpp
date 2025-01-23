#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    int count=std::atoi(argv[1]);
    std::cout<<"Max Threads = "<<std::thread::hardware_concurrency()<<std::endl;
    std::vector<std::thread> threads;
    auto func=[](int i){std::this_thread::sleep_for(std::chrono::seconds(1));};
    for (int i=0;i<count;i++){
        threads.emplace_back(func,1);
    }
    cout<<"created "<<count<<" threads "<<endl;
    std::for_each(threads.begin(), threads.end(), std::mem_fn(std::thread::join));
}