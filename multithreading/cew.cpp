#include <iostream>
#include <atomic>

int main(){

    std::atomic<int> V{2};

    int x = V.load();
    while(!V.compare_exchange_weak(x,5)){ std::cout<<"1"<<std::endl;};
    while(!V.compare_exchange_weak(x,10)){ std::cout<<"2"<<std::endl;};;
    int y  = V.load();
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;
    return 0;
}