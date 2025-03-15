#include <iostream>
#include <mutex>
#include <chrono>
#include <vector>

#include "spinlock.h"

void spinlock_test(HS::SpinLock &lock, std::atomic<int> &counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        lock.lock();
        ++counter;
        lock.unlock();
    }
}

void mutex_test(std::mutex &m, std::atomic<int> &counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::lock_guard<std::mutex> guard(m);
        ++counter;
    }
}

int main() {
    const int num_threads = 200;
    const int iterations = 1000000; // Number of increments per thread

    // SpinLock test
    std::atomic<int> spinlock_counter(0);
    HS::SpinLock spinlock;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> spinlock_threads;
    for (int i = 0; i < num_threads; ++i) {
        spinlock_threads.push_back(std::thread(spinlock_test, std::ref(spinlock), std::ref(spinlock_counter), iterations));
    }

    for (auto &t : spinlock_threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto spinlock_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "SpinLock completed in " << spinlock_duration.count() << " ms\n";
    std::cout << "SpinLock final counter: " << spinlock_counter.load() << "\n";

    // Mutex test
    std::atomic<int> mutex_counter(0);
    std::mutex m;
    start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> mutex_threads;
    for (int i = 0; i < num_threads; ++i) {
        mutex_threads.push_back(std::thread(mutex_test, std::ref(m), std::ref(mutex_counter), iterations));
    }

    for (auto &t : mutex_threads) {
        t.join();
    }

    end = std::chrono::high_resolution_clock::now();
    auto mutex_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Mutex completed in " << mutex_duration.count() << " ms\n";
    std::cout << "Mutex final counter: " << mutex_counter.load() << "\n";

    return 0;
}