#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

using namespace std;

shared_mutex sh_mx;

int reader_count=0;

void reader(){
    shared_lock<shared_mutex> shl(sh_mx);
    cout<<"reader_count "<<reader_count++<<endl;
    this_thread::sleep_for(chrono::seconds(4));
}
void writer(){
    lock_guard<shared_mutex> shg(sh_mx);
    cout<<"Writer "<<endl;
    this_thread::sleep_for(chrono::seconds(2));
}

int main(){
    vector<thread> threads;
    for (int i=0;i<1;++i){
        threads.emplace_back(writer);
    }
    for (int i=0;i<5;++i){
        threads.emplace_back(reader);
    }
    for (auto & t: threads) t.join();
}