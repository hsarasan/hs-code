#include <string>
#include <climits>
#include <mutex>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <benchmark/benchmark.h>

static void add1(benchmark::State& state){
    std::mutex m;
    
  for (auto _ : state) {
    std::mutex m;
    int i=0;
    auto fn=[&](){
        while(i<10000){
            std::lock_guard<std::mutex> l(m);
            i++;        
        }
    };
    std::vector<std::thread> threads;
    for (int i=0;i<10;i++)
    {
        threads.emplace_back(fn);
    }
    std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join));
  }
}

static void add2(benchmark::State& state){
    
  for (auto _ : state) {

    std::atomic<int> V{0};
    auto fn=[&](){
        while(V.load()<10000){
            V++;        
        }
    };
    std::vector<std::thread> threads;
    for (int i=0;i<10;i++)
    {
        threads.emplace_back(fn);
    }
    std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join));
  }
}

BENCHMARK(add1);
BENCHMARK(add2);
BENCHMARK_MAIN();