#include <iostream>
#include <atomic>
#include <optional>

using namespace std;

template <typename T>
struct MPMC{

    MPMC(int capacity):capacity(capacity+1){
        buffer = new T[capacity];
    }
    ~MPMC(){
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
            do{
                int current_head=head.load(memory_order_acquire);
            }while(!head.compare_exchange_weak(current_head,(current_head+1)%capacity,memory_order_acq_rel));
            buffer[current_head]=item;
        }
    }
    optional<T> pop(){
        
        do{
            if (isEmpty()) return nullopt;
            int read_pos=tail.load(memory_order_acquire);
        }while(!tail.compare_exchange_weak(read_pos,(read_pos+1)%capacity,memory_order_acq_rel));
        return buffer[read_pos];
    }

    private:
        atomic<int> head{0};
        atomic<int> tail{0};
        int capacity;
        T * buffer{nullptr};
};

int main(){
    MPMC<int> q(2);
    q.push(10);
    q.push(20);
    cout<<*(q.pop())<<endl;
    q.push(30);
    cout<<*(q.pop())<<endl;
    cout<<*(q.pop())<<endl;
    return 0;
}