/* Single Customer , Single Producer Q
Only size needs to be atomic */

#include <thread>
#include <iostream>
#include <atomic>

template <int N>
class SPSCQ{
    std::array<int, N> Q;
    int writePos;
    int readPos;
    std::atomic<size_t> size_v;

    public:

        int pop(){
            if (size_v.load()>0){
                auto value=Q[readPos];
                readPos=(readPos+1)%N;
                size_v.fetch_sub(1);
                return value;
            }
            return -1;
        }
        void push(int value){
            if (size_v.load()==N) {
                std::cout<<"Q full"<<std::endl;
                return ;
            }
            writePos=(writePos+1)%N;
            Q[writePos]=value;
            size_v.fetch_add(1);
        }
        auto size() { return size_v.load();}
};

SPSCQ<10> Q;

void write_fn(){
    int i=0;
    while (i<100){
        Q.push(i);
        int sz=Q.size();
        std::cout<<"Size from W = "<<sz<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        i++;
    }
}
void read_fn(){
    int i=0;
    while (i<100){
        int x = Q.pop();
        std::cout<<x<<std::endl;
        int sz=Q.size();
        std::cout<<"Size from R = "<<sz<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        i++;
    }
}
int main(){
    
    auto writeThread = std::jthread(write_fn);
    auto readThread = std::jthread(read_fn);
    return 0;
}