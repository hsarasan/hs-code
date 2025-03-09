#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

std::mutex mx;

void increment_integer(int& counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
				lock_guard<mutex> lg(mx);
        ++counter;  // Regular integer increment
    }
}

void increment_atomic(std::atomic<int>& counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);  // Atomic increment
    }
}

static void BM_RegularInteger(benchmark::State& state) {
    const int num_threads = 5;
    const int iterations = 1000000;
    int counter_int = 0;

    for (auto _ : state) {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.push_back(std::thread(increment_integer, std::ref(counter_int), iterations));
        }
        for (auto& t : threads) {
            t.join();
        }
    }
}

static void BM_AtomicInteger(benchmark::State& state) {
    const int num_threads = 5;
    const int iterations = 1000000;
    std::atomic<int> counter_atomic(0);

    for (auto _ : state) {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.push_back(std::thread(increment_atomic, std::ref(counter_atomic), iterations));
        }
        for (auto& t : threads) {
            t.join();
        }
    }
}

BENCHMARK(BM_RegularInteger);
BENCHMARK(BM_AtomicInteger);

BENCHMARK_MAIN();
