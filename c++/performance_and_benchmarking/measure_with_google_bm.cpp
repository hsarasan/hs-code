/*
    https://quick-bench.com/q/AVtXfdrFV6o-y8U0KKj_N_6-vkQ
*/

#include <benchmark/benchmark.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>

template <typename Container>
void fill_and_add(Container v){
    std::iota(v.begin(), v.end(), 0);
    auto sum=std::accumulate(v.begin(), v.end(), 0);     
}

// Benchmark for string creation
static void BM_UsingVector(benchmark::State& state) {
    for (auto _ : state) {
        fill_and_add(std::vector<int>(100000));
    }
}
BENCHMARK(BM_UsingVector);

// Benchmark for string copy
static void BM_UsingArray(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state) {
        fill_and_add(std::array<int,100000>());
    }
}
BENCHMARK(BM_UsingArray);

// Main entry point for Google Benchmark
BENCHMARK_MAIN();
