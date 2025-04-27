#include <iostream>
#include <atomic>
#include <optional>

using namespace std;

template <typename T>
struct SPSC{

    SPSC(int capacity):capacity(capacity+1){
        buffer = new T[capacity];
    }
    ~SPSC(){
        delete[] buffer;
    }
    bool isEmpty(){ 
        return head.load(memory_order_acquire)==tail.load(memory_order_acquire);
    }
    bool isFull(){
        int next_head=head.load(memory_order_acquire);
        next_head=(next_head+1)%capacity;
        return next_head==tail.load(memory_order_acquire);
    }
    void push(const T& item){
        if (!isFull()){
            buffer[head.load(memory_order_acquire)]=item;
            int next_head=(head.load(memory_order_acquire)+1)%capacity;
            head.store(next_head,memory_order_release);
        }
    }
    optional<T> pop(){
        if (isEmpty()) return nullopt;
        int read_pos=tail.load(memory_order_acquire);
        auto value=buffer[read_pos];
        tail.store((read_pos+1)%capacity,memory_order_release);
        return value;
    }

    private:
        atomic<int> head{0};
        atomic<int> tail{0};
        int capacity;
        T * buffer{nullptr};
};

int main(){
    SPSC<int> q(2);
    q.push(10);
    q.push(20);
    cout<<*(q.pop())<<endl;
    q.push(30);
    cout<<*(q.pop())<<endl;
    cout<<*(q.pop())<<endl;
    return 0;
}