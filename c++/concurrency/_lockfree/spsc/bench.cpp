#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <boost/lockfree/spsc_queue.hpp>
#include "ring_buffer.h"

// Benchmark Configuration
constexpr size_t TEST_DURATION = 10;  // Seconds
constexpr size_t xBUFFER_SIZE = 1024;

// Define Boost.Lockfree SPSC Queue
boost::lockfree::spsc_queue<int, boost::lockfree::capacity<xBUFFER_SIZE>> boost_queue;

// Custom RingBuffer Instance
RingBuffer<int> custom_ring;

// Throughput Counters
std::atomic<size_t> boost_produced{0}, boost_consumed{0};
std::atomic<size_t> ring_produced{0}, ring_consumed{0};

// Exit flag for all threads
std::atomic<bool> exit_flag{false};

// --- BOOST.LOCKFREE PRODUCER ---
void boost_producer() {
    std::cout << "[Boost Producer] Started\n";
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        int value = boost_produced++;
        while (!boost_queue.push(value)) {
            std::this_thread::yield();
        }

        auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
        if (elapsed >= TEST_DURATION) {
            exit_flag.store(true);  // Set exit flag after test duration
            break;  // Exit after TEST_DURATION
        }
    }
    std::cout << "[Boost Producer] Exiting\n";
}

// --- BOOST.LOCKFREE CONSUMER ---
void boost_consumer() {
    std::cout << "[Boost Consumer] Started\n";
    while (!exit_flag.load() || boost_produced.load() != boost_consumed.load()) {
        int value;
        while (!boost_queue.pop(value)) {
            std::this_thread::yield();
        }
        boost_consumed++;
    }
    std::cout << "[Boost Consumer] Exiting\n";
}

// --- CUSTOM RINGBUFFER PRODUCER ---
void ring_producer() {
    std::cout << "[Ring Producer] Started\n";
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        int value = ring_produced++;
        while (!custom_ring.enqueue(value)) {
            std::this_thread::yield();
        }

        auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
        if (elapsed >= TEST_DURATION) {
            exit_flag.store(true);  // Set exit flag after test duration
            break;  // Exit after TEST_DURATION
        }
    }
    std::cout << "[Ring Producer] Exiting\n";
}

// --- CUSTOM RINGBUFFER CONSUMER ---
void ring_consumer() {
    std::cout << "[Ring Consumer] Started\n";
    while (!exit_flag.load() || ring_produced.load() != ring_consumed.load()) {
        int value;
        while (!custom_ring.dequeue(value)) {
            std::this_thread::yield();
        }
        ring_consumed++;
    }
    std::cout << "[Ring Consumer] Exiting\n";
}

int main() {
    std::cout << "Starting Benchmark...\n";

    // Launch Benchmark for Boost.Lockfree SPSC Queue
    std::cout << "[Boost] Running producer and consumer threads...\n";
    std::thread boost_prod(boost_producer);
    std::thread boost_cons(boost_consumer);
    boost_prod.join();
    boost_cons.join();

		exit_flag.store(false);
    
    // Launch Benchmark for Custom RingBuffer
    std::cout << "[RingBuffer] Running producer and consumer threads...\n";
    std::thread ring_prod(ring_producer);
    std::thread ring_cons(ring_consumer);
    ring_prod.join();
    ring_cons.join();

    // Print Results
    std::cout << "[Benchmark Finished]\n";
    std::cout << "[Boost.Lockfree] Throughput: " << boost_produced.load() / TEST_DURATION << " messages/sec\n";
    std::cout << "[RingBuffer] Throughput: " << ring_produced.load() / TEST_DURATION << " messages/sec\n";

    return 0;
}

