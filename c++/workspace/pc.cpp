#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <semaphore>
#include <queue>

using namespace std;

queue<int> Q;
mutex q_mx;
counting_semaphore<1> empty_slots(1),filled_slots(0);

void producer(){
    for (int i=0;i<6;++i){
        empty_slots.acquire();
        {
            lock_guard<mutex> lg(q_mx);
            Q.push(i);
        }
        filled_slots.release();
        this_thread::sleep_for(chrono::seconds(1));
    }
}
void consumer(int id){
    for (int i=0;i<3;++i){
        filled_slots.acquire();
        {
            lock_guard<mutex> lg(q_mx);
            int item=Q.front();
            cout<<"Consumer "<<id<<" processing "<<item<<endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        empty_slots.release();
    }
}
int main(){
    vector<thread> threads;
        
    threads.emplace_back(producer);
    threads.emplace_back(consumer,1);
    threads.emplace_back(consumer,2);
    for (auto & t: threads) t.join();
}