#include <iostream>
#include <vector>
#include <thread>
#include <unordered_set>
#include "lfstack.h"  

constexpr int NUM_THREADS = 10;
constexpr int OPERATIONS_PER_THREAD = 1000;

void pushTask(HS::LFStack<int>& stack, int thread_id, std::vector<int>& pushed_values) {
    for (int i = 0; i < OPERATIONS_PER_THREAD; ++i) {
        int value = thread_id * OPERATIONS_PER_THREAD + i;
        stack.push(value);
        pushed_values.push_back(value);  // Store values for later verification
    }
}

void popTask(HS::LFStack<int>& stack, std::vector<int>& popped_values) {
    for (int i = 0; i < OPERATIONS_PER_THREAD; ++i) {
        auto val = stack.pop();
        if (val) {
            popped_values.push_back(*val);
        }
    }
}

int main() {
    HS::LFStack<int> stack;
    
    std::vector<std::thread> push_threads, pop_threads;
    std::vector<std::vector<int>> pushed_values(NUM_THREADS);
    std::vector<std::vector<int>> popped_values(NUM_THREADS);

    // Launch multiple push threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        push_threads.emplace_back(pushTask, std::ref(stack), i, std::ref(pushed_values[i]));
    }

    // Wait for all push threads to finish
    for (auto& t : push_threads) {
        t.join();
    }

    // Launch multiple pop threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pop_threads.emplace_back(popTask, std::ref(stack), std::ref(popped_values[i]));
    }

    // Wait for all pop threads to finish
    for (auto& t : pop_threads) {
        t.join();
    }

    // Verify correctness: All pushed values should be in the popped values
    std::unordered_set<int> pushed_set;
    for (const auto& vec : pushed_values) {
        for (int val : vec) {
            pushed_set.insert(val);
        }
    }

    std::unordered_set<int> popped_set;
    for (const auto& vec : popped_values) {
        for (int val : vec) {
            popped_set.insert(val);
        }
    }

    if (pushed_set == popped_set) {
        std::cout << "Test Passed: All pushed values were successfully popped!" << std::endl;
    } else {
        std::cout << "Test Failed: Mismatch between pushed and popped values!" << std::endl;
        std::cout << "Pushed size: " << pushed_set.size() << ", Popped size: " << popped_set.size() << std::endl;
    }

    return 0;
}