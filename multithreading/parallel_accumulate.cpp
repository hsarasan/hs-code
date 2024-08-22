#include <iostream>
#include <algorithm>
#include <thread>
#include <functional>
#include <numeric>
#include <vector>

template <typename T, typename Iterator>
struct accumulate_block {
    void operator() (Iterator first , Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }

};

template <typename T, typename Iterator>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    int num_threads = std::thread::hardware_concurrency() - 2;
    auto block_size = std::distance(first, last)/num_threads;
    std::vector<T> result(num_threads);
    std::vector<std::thread> threads;

    Iterator block_start=first;
    for(unsigned long i=0;i<num_threads;++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        if (i==num_threads-1) block_end = last;
        threads.emplace_back( std::thread( accumulate_block<T,Iterator>(), block_start,block_end,std::ref(result[i])));
        block_start=block_end;        
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(std::thread::join));
    return std::accumulate(result.begin(), result.end(), 0);
}

int main() {

    std::vector<int> v(100);
    int counter=0;
    std::for_each(v.begin(), v.end(), [&](int &i){i=counter++;});
    int result{0};
    using Iterator = decltype(v.begin());
    result = parallel_accumulate<int, Iterator> (v.begin(), v.end(), result);
    std::cout<<"Result "<<result<<std::endl;
}
