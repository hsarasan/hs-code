#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <syncstream>

using namespace std;

mutex mx;
condition_variable cv;
queue<int> Q;
atomic<bool> stop_flag{false};

void consumer(){
    while(true){
        unique_lock<mutex> ul(mx);
        cv.wait(ul,[](){return stop_flag.load()||!Q.empty();});
        if (stop_flag.load()==true) return;
        osyncstream out(cout);
        out<<"Processing "<<Q.front()<<endl;
        Q.pop();
    }
}
void producer(int multiplier){
    for (int i=0;i<5;++i){
        Q.push(multiplier+i);
        cv.notify_one();
    }
}
int main(){
    vector<thread> producers;
    vector<thread> consumers;
    for (int i=0;i<3;++i){
        producers.emplace_back(producer,i*10);
    }
    for (int i=0;i<2;++i){
        consumers.emplace_back(consumer);
    }
    this_thread::sleep_for(chrono::seconds(5));
    stop_flag.store(true);
    cv.notify_all();
    for (auto &producer: producers) producer.join();
    for (auto &consumer: consumers) consumer.join();
    return 0;
}