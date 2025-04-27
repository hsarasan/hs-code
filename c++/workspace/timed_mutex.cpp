#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

timed_mutex tmx;

int reader_count=0;

void reader(){
    lock_guard<timed_mutex> lg(tmx);
    cout<<"reader locked "<<endl;
    this_thread::sleep_for(chrono::seconds(3));
}
void writer(){
    if (tmx.try_lock_for(chrono::seconds(2))){
        cout<<"Writer locked"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    else {
        cout<<"Writer lock failed"<<endl;
    }
}

int main(){
    vector<thread> threads;
        
    threads.emplace_back(writer);
    threads.emplace_back(reader);
    for (auto & t: threads) t.join();
}