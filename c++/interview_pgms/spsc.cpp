#include <iostream>
#include <atomic>
#include <vector>
#include <optional>

using namespace std;

template <typename T, int capacity>
struct SPSC{
    explicit SPSC(){}
    bool isEmpty(){ return head.load(memory_order_acquire)==tail.load(memory_order_acquire);}
    bool isFull(){ 
        auto new_head=(head.load(memory_order_acquire)+1)%max_size;
        return new_head==tail.load(memory_order_acquire);
    }
    bool push(const T& item){
        if (isFull()){ return false; }
        auto new_head=(head.load(memory_order_acquire)+1)%max_size;
        auto current_head=head.load(memory_order_acquire);
        buffer[current_head]=item;
        head.store(new_head,memory_order_release);
        return true;
    }
    optional<T> pop(){
        if (isEmpty()) return nullopt;
        T item=buffer[tail.load(memory_order_acquire)];
        auto new_tail=(tail.load(memory_order_acquire)+1)%max_size;
        tail.store(new_tail,memory_order_release);
        return item;
    }   
    private:
        constexpr static int max_size{capacity+1};
        T buffer[max_size];
        atomic<int> head{0};
        atomic<int> tail{0};    
};

int main(){

    SPSC<int,3> Q;
    cout<<Q.push(1)<<endl;
    cout<<Q.push(2)<<endl;
    auto ret=Q.pop();
    if (ret.has_value()) {
        cout<<"Return="<<ret.value()<<endl;
    }
    cout<<Q.push(3)<<endl;
    ret=Q.pop();
    if (ret.has_value()) {
        cout<<"Return="<<ret.value()<<endl;
    }
    ret=Q.pop();
    if (ret.has_value()) {
        cout<<"Return="<<ret.value()<<endl;
    }
    Q.push(4);
    ret=Q.pop();
    if (ret.has_value()) {
        cout<<"Return="<<ret.value()<<endl;
    }
    Q.push(5);
    Q.push(6);
    ret=Q.pop();
    if (ret.has_value()) {
        cout<<"Return="<<ret.value()<<endl;
    }

}