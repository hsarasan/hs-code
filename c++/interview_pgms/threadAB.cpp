#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

using namespace std;

mutex m;
condition_variable cv;
atomic<int> turn;
void print(char c,int my_turn){
    while(true){
        unique_lock<mutex> ul(m);
        cv.wait(ul, [&](){return turn==my_turn;});
        cout<<c;
        this_thread::sleep_for(chrono::seconds(1));
        int next_turn=turn.load();
        next_turn=(next_turn+1)%3;
        turn.store(next_turn);
        cv.notify_all();
    }    
}

int main(){
    auto A=thread(print,'A',0);
    auto B=thread(print,'B',1);
    auto C=thread(print,'C',2);
    A.join();
    B.join();
    C.join();
    return 0;
}