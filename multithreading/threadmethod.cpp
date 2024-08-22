#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>

std::mutex mx;
class Worker{

    bool active{false};
    public:
        void doSomething(){
            std::unique_lock<std::mutex> lock(mx);
            std::cout<<"Executing "<<std::this_thread::get_id()<<std::endl;
            lock.unlock();
            if (active)
            {
                std::this_thread::sleep_for(std::chrono::seconds(10));
            }
        }
        void setActive() { active = true; }
};

int main()
{
    std::vector<Worker> v(10);
    std::vector<std::thread> tv;
    std::for_each(v.begin(), v.end(), std::mem_fn(Worker::setActive));
    std::for_each(v.begin(), v.end(), [&](Worker & elem) {
        auto tid=std::thread(&Worker::doSomething, elem);
        tv.emplace_back(std::move(tid));
    }
    );
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::for_each(tv.begin(), tv.end(), std::mem_fn(&std::thread::join));
}