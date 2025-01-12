#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

std::vector<int> x;

template <typename T>
class ThreadSafeQ {

    std::queue<T> Q;
    std::mutex m;
    std::condition_variable cv;
    public:

        ThreadSafeQ()
        {
            
        }

        void push(T val)
        {
            std::lock_guard<std::mutex> lock(m);
            Q.push(val);
            cv.notify_one();
        }
        std::shared_ptr<T> pop()
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [&](){ return !Q.empty(); });
            auto ret = std::make_shared<T>(Q.front());
            Q.pop();
            return ret;
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lock(m);
            return Q.empty();
        }

};

ThreadSafeQ<int> gQ;

void producer()
{
    for (int i=0;i<20;++i)
    {
        std::cout<<"Producer Writing "<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        gQ.push(i);
    }
}
void consumer()
{
    int counter;
        auto readV = gQ.pop();
        std::cout<< std::this_thread::get_id() <<" Consumer processed "<<*readV<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        counter++;
}

int main()
{

    auto producerThread = std::thread(producer);
    std::vector<std::thread> v;
    for (int i=0; i<10; ++i)
    {
        v.emplace_back(std::thread(consumer));
    }
    
    producerThread.join();
    std::for_each(v.begin(), v.end(), std::mem_fn(std::thread::join));
}