#include <iostream>
#include <thread>
#include <vector>
#include <optional>
#include <atomic>
#include <iterator>
#include <algorithm>
#include <functional>
#include <chrono>
#include <mutex>
#include <cassert>

using namespace std;

//head - where producer next writes to
//tail - where conumser next reads from
//Q Empty - head==tail
//Q Full - (tail+1)%capacity == head
template <typename T, int Capacity=10>
class SPMCQ{
    public:
        explicit SPMCQ(): buffer(Capacity){
            reader_position.store(0);
            size.store(0);
            writer_position.store(0);
        }
        bool isQFull(){
            return (size.load(memory_order_acquire)==Capacity);
        }
        bool isQEmpty(){
            return size.load(memory_order_acquire)==0;
        }
        bool enqueue(T value){
            if (isQFull()){
                return false;
            }
            int current_write_position = writer_position.load(memory_order_acquire);
            int current_size = size.load(memory_order_acquire);
            buffer[current_write_position]=value;
            size.store(current_size+1,memory_order_release);
            writer_position.store((current_write_position+1)%Capacity,memory_order_release);
            return true;
        }

        std::optional<T> dequeue(){
            if (isQEmpty()) {
                return std::nullopt;
            }
            int current_read_position = reader_position.load(memory_order_acquire);
            int current_size = size.load(memory_order_acquire);
            T item = buffer[current_read_position];
            reader_position.store((current_read_position +1)%Capacity, memory_order_release);
            size.store(current_size-1,memory_order_release);
            return item;
        }

        void print(){
            copy(buffer.begin(), buffer.end(), ostream_iterator<T>(cout,","));
            cout<<"==> reader_pos="<<reader_position.load()<<" sz="<<size.load()<<endl;
        }
    private:
        vector<T> buffer;
        atomic<size_t> writer_position;
        atomic<size_t> reader_position;
        atomic<size_t> size;
      
};


mutex m;
vector<int> results;
int N=1000;
atomic<bool> done{false};

void producer(SPMCQ<int>& queue) {
    for (int i = 0; i < N; ++i) {
        while (!queue.enqueue(i)) {
            std::this_thread::yield(); // Wait until the queue has space
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
}

void consumer(SPMCQ<int>& queue, int id) {
    while (!done.load()) {
        auto item = queue.dequeue();
        if (item) {
            lock_guard<mutex> lg(m);
            std::cout << "Consumer " << id << " consumed: " << *item << "\n";
            results.push_back(*item);
        } else {
            std::this_thread::yield(); // Wait until the queue has items
        }
    }
}

void analyzeresults(){
    cout<<results.size()<<" "<<N<<endl;
    assert(results.size()==N);
}

int main(){
    SPMCQ<int> Q;
    std::optional<int> item;
    std::thread producer_thread(producer, std::ref(Q));
    const size_t consumer_count = 3;
    std::vector<std::thread> consumer_threads;
    for (size_t i = 0; i < consumer_count; ++i) {
      consumer_threads.emplace_back(consumer, std::ref(Q), i + 1);
    }
    producer_thread.join();
    done.store(true);
    for_each(consumer_threads.begin(), consumer_threads.end(), std::mem_fn(std::thread::detach));
    analyzeresults();
    return 0;

}