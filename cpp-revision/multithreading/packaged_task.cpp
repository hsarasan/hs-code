#include <iostream>
#include <thread>
#include <future>

using namespace std;

int add(int a, int b){
    return a+b;
}

int main(){
    packaged_task<int(int,int)> pt(add);
    auto fut=pt.get_future();
    auto tid=thread(move(pt),20,40);
    cout<<fut.get()<<endl;
    tid.join();
    return 0;
}