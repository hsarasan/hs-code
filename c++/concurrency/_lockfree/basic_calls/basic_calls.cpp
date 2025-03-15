#include <iostream>
#include <thread>
#include <atomic>

struct S{
    float x;
    int y;
    char z[20];
};
using namespace std;

int main(){
    cout<<"L1 Cache Line Size => "<<hardware_destructive_interference_size<<endl;
    cout<<"No of Logical Processors => "<<thread::hardware_concurrency()<<endl;
    atomic<double> x;
    cout<<"atomic<double> Is Lock Free? " << x.is_lock_free()<<endl;
    atomic<long long> y;
    cout<<"atomic<long long> Is Lock Free? " << y.is_lock_free()<<endl;

    return 0;
}