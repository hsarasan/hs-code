#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

struct spinLock{
    atomic<int> next_turn{0};
    atomic<int> current_turn{0};
    void lock(){
        int my_turn=next_turn.fetch_add(1);
        while(current_turn.load()!=my_turn){}
    }
    void unlock(){
        current_turn.fetch_add(1);
    }
};

int main(){
    return 0;
}