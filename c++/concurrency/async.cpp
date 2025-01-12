#include <thread>
#include <iostream>
#include <atomic>
#include <future>

using namespace std;

static int gettimeout(){
    srand(time(nullptr));
    int wait_time=rand()%10;
    return wait_time;
}

int task1(){
    int wait_time=gettimeout();
    this_thread::sleep_for(chrono::seconds(wait_time));
    return wait_time;
}
int main(){
    auto fut1(std::async(task1));
    auto fut2(async(task1));
    cout<<"T3="<<task1()<<endl;
    cout<<"T1="<<fut1.get()<<endl;
    cout<<"T2="<<fut2.get()<<endl;
}