#include <iostream>
#include <shared_mutex>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

shared_mutex sh_mx;
int var{0};
void writer(){
    for (int i=0; i<4;++i){
        unique_lock<shared_mutex> ul(sh_mx);
        var++;
        cout<<"Writing by thread "<<this_thread::get_id()<<endl;
    }
}
void reader(){
    for (int i=0;i<3;++i){
        shared_lock<shared_mutex> sl(sh_mx);
        cout<<"Read by thread "<<this_thread::get_id<<"=>"<<var<<endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(){
    vector<thread> threads;
    for (int i=0;i<3;++i){
        threads.emplace_back(reader);
    }
    for (int i=0;i<2;++i){
        threads.emplace_back(writer);
    }
    for (auto &t: threads){
        t.join();
    }
    return 0;
}