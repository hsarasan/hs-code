#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

atomic_flag flag{false};

void s_lock(){
    while(flag.test_and_set()){}
}
void s_unlock(){
    flag.clear();
}
int val{0};
int main(){

    auto t1=std::thread([&](){
        for (int i=0; i<1000000; ++i) 
            s_lock();
                val++;
            s_unlock();
        }
        );
    auto t2=std::thread([&](){
        for (int i=0; i<1000000; ++i)
            s_lock(); 
                val--;
            s_unlock();
        }
        );
    t1.join();
    t2.join();
    cout<<"val="<<val<<endl;
}