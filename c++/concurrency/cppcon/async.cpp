#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

int func(){
    cout<<"Invoked "<<endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"Returning "<<endl;
    return 10;
}

int main(){

    auto fut = async(func);
    cout<<fut.get()<<endl;

}