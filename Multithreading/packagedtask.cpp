#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <algorithm>

int sqr(int v)
{
    return v*v;
}

using sqr_function = std::packaged_task<int (int)>;

int main() {

    std::vector<std::shared_future<int>> tasks1;
    std::vector<std::shared_future<int>> tasks2;
    std::vector<std::thread> threads;
    for (int i=0;i<10;++i)
    {
        sqr_function pt(sqr);
        std::shared_future<int> sf1(std::move(pt.get_future()));
        auto sf2 = sf1;
        tasks1.emplace_back(sf1);
        tasks2.emplace_back(sf2);
        threads.emplace_back(std::thread(std::move(pt), i));
    }   
    
    std::for_each(tasks1.begin(), tasks1.end(), [](std::shared_future<int> &fut){ std::cout<<fut.get()<< " ";});
    std::cout<<std::endl;
    std::for_each(tasks2.begin(), tasks2.end(), [](std::shared_future<int> &fut){ std::cout<<fut.get()<< " ";});
    std::cout<<std::endl;
    
    std::for_each(threads.begin(), threads.end(), std::mem_fn(std::thread::join));
}