#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

int main(){
    cout<<hardware_destructive_interference_size<<endl;
    cout<<hardware_constructive_interference_size<<endl;
    cout<<thread::hardware_concurrency()<<endl;
}