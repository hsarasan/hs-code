#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <stack>
#include <mutex>
#include <optional>
#include "lfstack.h"  // Include your lock-free stack header

constexpr int MAX_THREADS = 128;
constexpr int OPERATIONS_PER_THREAD = 100000;

// **Wrapper for Lock-Free Stack**
template <typename T>
class LFStackWrapper {
private:
    HS::LFStack<T> stack;
public:
    void push(const T& value) { stack.push(value); }
    std::optional<T> pop() { return stack.pop(); }
};

// **Wrapper for std::stack + std::mutex**
template <typename T>
class StdStackWrapper {
private:
    std::stack<T> stack;
    std::mutex mtx;
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        stack.push(value);
    }
    
    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (stack.empty()) return std::nullopt;
        T value = stack.top();
        stack.pop();
        return value;
    }
};

// **Benchmark Push Performance**
template <typename StackType>
void benchmark_push(StackType& stack, int num_threads, const std::string& name) {
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < OPERATIONS_PER_THREAD; ++j) {
                stack.push(j);
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(end - start).count();

    std::cout << name << " Push (" << num_threads << " threads): " 
              << (num_threads * OPERATIONS_PER_THREAD) / elapsed 
              << " ops/sec (" << elapsed << " sec)" << std::endl;
}

// **Benchmark Pop Performance**
template <typename StackType>
void benchmark_pop(StackType& stack, int num_threads, const std::string& name) {
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < OPERATIONS_PER_THREAD; ++j) {
                stack.pop();
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(end - start).count();

    std::cout << name << " Pop (" << num_threads << " threads): " 
              << (num_threads * OPERATIONS_PER_THREAD) / elapsed 
              << " ops/sec (" << elapsed << " sec)" << std::endl;
}

// **Run Benchmark Tests**
int main() {
    for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads *= 2) {
        std::cout << "\n=== Benchmarking with " << num_threads << " threads ===\n";

        LFStackWrapper<int> lf_stack;
        StdStackWrapper<int> std_stack;

        // Benchmark Lock-Free Stack
        benchmark_push(lf_stack, num_threads, "Lock-Free Stack");
        benchmark_pop(lf_stack, num_threads, "Lock-Free Stack");

        // Benchmark std::stack with Mutex
        benchmark_push(std_stack, num_threads, "Mutex-Based Stack");
        benchmark_pop(std_stack, num_threads, "Mutex-Based Stack");
    }

    return 0;
}
