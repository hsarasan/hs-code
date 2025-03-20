#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <syncstream>
#include <vector>

using namespace std;

int N=4;
mutex mx[4];
struct Philosopher{
    Philosopher(int id):id(id){}
    public:
        void start(){
            while(think_count<5){
                eat();
                think();
                think_count++;
            }
            osyncstream out(cout);
            out<<"Ph "<<id<<" going to sleep"<<endl;
        }
    private:
        int id;
        int think_count{0};
        void eat(){
            int left=(id+N-1)%N;
            int right=id;
            if (id%2==0){
                lock_guard<mutex> lg_right(mx[right]);
                lock_guard<mutex> lg_left(mx[left]);
                osyncstream out(cout);
                out<<"Ph "<<id<<" start eating "<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                out<<"Ph "<<id<<" finished eating "<<endl;
            }
            else{
                lock_guard<mutex> lg_left(mx[left]);
                lock_guard<mutex> lg_right(mx[right]);
                osyncstream out(cout);
                out<<"Ph "<<id<<" start eating "<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                out<<"Ph "<<id<<" finished eating "<<endl;
            }
        }
        void think(){
            osyncstream out(cout);
            out<<"Ph "<<id<<" start thinking "<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            out<<"Ph "<<id<<" finish thinking "<<endl;
        }
};


int main(){
    vector<thread> threads;
    vector<Philosopher> thinkers;
    for (int i=0;i<N;++i){
        thinkers.emplace_back(i);
    }
    for (int i=0;i<N;++i){
        threads.emplace_back(Philosopher::start,thinkers[i]);
    }
    for (auto & t: threads){
        if (t.joinable()) t.join();
    }
    return 0;
}