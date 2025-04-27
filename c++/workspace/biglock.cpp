#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex A, B;

int reader_count=0;

void funcAB(){
    lock_guard<mutex> lg(A);
    cout<<"A locked by AB"<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lg2(B);
    cout<<"B locked by AB"<<endl;
    this_thread::sleep_for(chrono::seconds(1));
}
void funcBA(){
    std::lock(A,B);
    cout<<"Big double lock by BA"<<endl;    
    lock_guard<mutex> lg(B,adopt_lock);
    cout<<"B locked by BA"<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lg2(A,adopt_lock);
    cout<<"A locked by BA"<<endl;
    this_thread::sleep_for(chrono::seconds(2));
}

int main(){
    vector<thread> threads;
        
    threads.emplace_back(funcAB);
    threads.emplace_back(funcBA);
    for (auto & t: threads) t.join();
}