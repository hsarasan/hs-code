#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <algorithm>
#include <list>
#include <iterator>
#include <cassert>
#include <numeric>

using namespace std;
std::vector<int> v(1000000);
std::atomic<bool> done{false};

void find_parallel(int start, int end){
    int n=end-start+1;
    //std::cout<<"start="<<start<<" end="<<end<<std::endl;
    int chunk=n/25;
    int i=0;
    while(i<25 && !done.load()){
        int chunk_start = start+chunk*i;
        int chunk_end   = chunk_start+chunk;
        i++;
        //std::cout<<"start="<<chunk_start<<" chunk_end="<<chunk_end<<std::endl;
        auto iter=find(v.begin()+chunk_start, v.begin()+chunk_end,888888);
        if (iter!=v.begin()+chunk_end){
            std::cout<<"found parallely"<<std::endl;
            done.store(true);
        }
    }
}
void find_standard(){
    auto iter=find(v.begin(), v.end(), 888888);
    if (iter!=v.end())
        std::cout<<"found standard "<<std::endl;
}

void execute_concurrent_find(){
    vector<thread> threads;
    for (int i=0;i<10;++i)
        threads.emplace_back(find_parallel, i*100000, (i+1)*100000);
    for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

void execute_standard_find(){
    find_standard();
}

/*
BENCHMARK Code
static void benchmarkfind_1(benchmark::State& state) {
  for (auto _ : state) {
    execute_concurrent_find();    
  }
}
BENCHMARK(benchmarkfind_1);

static void benchmarkfind_2(benchmark::State& state) {
  for (auto _ : state) {
    execute_standard_find();    
  }
}
BENCHMARK(benchmarkfind_2);
*/

int main(){
    std::iota(v.begin(),v.end(),0);
    execute_standard_find();
    execute_concurrent_find();
}