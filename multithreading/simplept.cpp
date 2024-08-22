#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <thread>
#include <iterator>
#include <numeric>
#include <functional>
#include <map>
#include <queue>
#include <atomic>
#include <future>
#include <chrono>
#include <condition_variable>

int square(int x ){
    return x*x;
}

std::queue<std::packaged_task<int()> > Q;
std::condition_variable cv;
std::mutex m;

void execute(){
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, [](){ return !Q.empty();});
    auto task = std::move(Q.front());
    Q.pop();
    task();
}
int main() { 
    std::thread t(execute);
    std::packaged_task<int()> pt(std::bind(square,9));
    auto fut = pt.get_future();
    {
        std::lock_guard<std::mutex> ul(m);
        Q.push(std::move(pt));
    }
    cv.notify_one();
    std::cout<<fut.get()<<std::endl;
    t.join();
    return 0 ;
}