#include <thread>
#include <chrono>

#include "spsc.h"

// Benchmark function
void benchmark_spsc_queue(size_t queue_size, size_t num_operations) {
    SPSCQueue<int> queue(queue_size);

    auto producer = [&]() {
        for (size_t i = 0; i < num_operations; ++i) {
            while (!queue.enqueue(i)) {
                // Queue is full, retry
            }
        }
    };

    auto consumer = [&]() {
        int item;
        for (size_t i = 0; i < num_operations; ++i) {
            while (!queue.dequeue(item)) {
                // Queue is empty, retry
            }
        }
    };

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    // Start producer and consumer threads
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    // Wait for threads to finish
    producer_thread.join();
    consumer_thread.join();

    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Queue size: " << queue_size
              << ", Operations: " << num_operations
              << ", Time: " << duration << " ms"
              << ", Average Time: " << (float)duration*1000*1000/num_operations << " micros\n";

}

int main() {
    // Benchmark with different queue sizes and operation counts
    benchmark_spsc_queue(1000, 1000000);  // Queue size 1000, 1M operations
    benchmark_spsc_queue(10000, 1000000); // Queue size 10000, 1M operations
    benchmark_spsc_queue(100000, 1000000); // Queue size 100000, 1M operations
    benchmark_spsc_queue(1000000, 1000000); // Queue size 1M, 1M operations

    return 0;
}