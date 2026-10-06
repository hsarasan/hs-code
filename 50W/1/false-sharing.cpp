#include <algorithm>
#include <atomic>
#include <barrier>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <thread>

constexpr std::size_t kIterations = 50'000'000;

struct ContendedCounter {
    std::atomic<std::uint64_t> value{0};
};

struct PaddedCounter {
    alignas(64) std::atomic<std::uint64_t> value{0};
};

template <typename Counter>
double benchmark(Counter* counters) {
    for (std::size_t i = 0; i < 2; ++i) {
        counters[i].value.store(0, std::memory_order_relaxed);
    }

    std::barrier sync(3);  // main thread + 2 workers

    auto worker = [&](int idx) {
        sync.arrive_and_wait();
        for (std::size_t i = 0; i < kIterations; ++i) {
            counters[idx].value.fetch_add(1, std::memory_order_relaxed);
        }
    };

    auto start = std::chrono::steady_clock::now();
    std::thread t0(worker, 0);
    std::thread t1(worker, 1);
    sync.arrive_and_wait();

    t0.join();
    t1.join();
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    std::cout << "False sharing demo in C++20\n";
    std::cout << "Cache line size: "
              << std::hardware_destructive_interference_size << " bytes\n\n";

    ContendedCounter contended[2];
    PaddedCounter padded[2];

    double bestContended = std::numeric_limits<double>::max();
    double bestPadded = std::numeric_limits<double>::max();

    for (int attempt = 0; attempt < 5; ++attempt) {
        bestContended = std::min(bestContended, benchmark(contended));
        bestPadded = std::min(bestPadded, benchmark(padded));
    }

    std::cout << "Contended (adjacent counters): " << bestContended << " ms\n";
    std::cout << "Padded    (cache-line-aligned): " << bestPadded << " ms\n";
    std::cout << "Speedup: " << bestContended / bestPadded << "x\n";

    return 0;
}
