#include <iostream>
#include <boost/lockfree/spsc_queue.hpp>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstring>
#include <unistd.h>  // For usleep()

constexpr int BUFFER_SIZE = 256;
constexpr int MESSAGE_SIZE = 64;
constexpr int TEST_DURATION = 10;  // Run test for 10 seconds

struct Message {
    char data[MESSAGE_SIZE];
};

// --- HS Ring Buffer Implementation ---
struct RingBuffer {
    std::atomic<uint32_t> head{0};
    std::atomic<uint32_t> tail{0};
    char buffer[BUFFER_SIZE][MESSAGE_SIZE];
};

RingBuffer ring;  // Global ring buffer

// --- Boost.Lockfree Implementation ---
boost::lockfree::spsc_queue<Message, boost::lockfree::capacity<BUFFER_SIZE>> boost_queue;

// --- Global Running Flag for Thread Termination ---
std::atomic<bool> running{true};

// --- HS Producer ---
void hs_spsc_producer(int &count) {
    while (running.load(std::memory_order_relaxed)) {
        uint32_t head = ring.head.load(std::memory_order_relaxed);
        uint32_t tail = ring.tail.load(std::memory_order_acquire);

        if ((head + 1) % BUFFER_SIZE == tail) {
            usleep(1);  // Avoid busy waiting
            continue;  // Buffer full
        }

        snprintf(ring.buffer[head], MESSAGE_SIZE, "Message %d", count++);
        ring.head.store((head + 1) % BUFFER_SIZE, std::memory_order_release);
    }
}

// --- HS Consumer ---
void hs_spsc_consumer(int &consumed) {
    while (running.load(std::memory_order_relaxed)) {
        uint32_t head = ring.head.load(std::memory_order_acquire);
        uint32_t tail = ring.tail.load(std::memory_order_relaxed);

        if (head == tail && running.load(std::memory_order_relaxed)) {
            usleep(1);  // Avoid busy waiting if the buffer is empty
            continue;  // Buffer empty, continue checking
        }

        char message[MESSAGE_SIZE];
        strncpy(message, ring.buffer[tail], MESSAGE_SIZE);
        ring.tail.store((tail + 1) % BUFFER_SIZE, std::memory_order_release);
        consumed++;
    }
}

// --- Boost.Lockfree Producer ---
void boost_producer(int &count) {
    while (running.load(std::memory_order_relaxed)) {
        Message msg;
        snprintf(msg.data, MESSAGE_SIZE, "Message %d", count++);

        if (!boost_queue.push(msg)) {
            usleep(1);  // Avoid busy waiting
            continue;  // Queue full
        }
    }
}

// --- Boost.Lockfree Consumer ---
void boost_consumer(int &consumed) {
    while (running.load(std::memory_order_relaxed)) {
        Message msg;
        if (!boost_queue.pop(msg) && running.load(std::memory_order_relaxed)) {
            usleep(1);  // Avoid busy waiting if the queue is empty
            continue;  // Queue empty, continue checking
        }

        consumed++;
    }
}

// --- Main Function (Running Both Benchmarks) ---
int main() {
    int hs_spsc_produced = 0, hs_spsc_consumed = 0;
    int boost_produced = 0, boost_consumed = 0;

    // Launch all threads
    std::thread hs_spsc_prod(hs_spsc_producer, std::ref(hs_spsc_produced));
    std::thread hs_spsc_cons(hs_spsc_consumer, std::ref(hs_spsc_consumed));
    std::thread boost_prod(boost_producer, std::ref(boost_produced));
    std::thread boost_cons(boost_consumer, std::ref(boost_consumed));

    // Run for TEST_DURATION seconds
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DURATION));

    // Signal all threads to stop
    running.store(false, std::memory_order_relaxed);

    // Wait for all threads to finish
    hs_spsc_prod.join();
    hs_spsc_cons.join();
    boost_prod.join();
    boost_cons.join();

    // Display results
    std::cout << "[HS RingBuffer] Produced: " << hs_spsc_produced << " messages in " << TEST_DURATION << " seconds\n";
    std::cout << "[HS RingBuffer] Consumed: " << hs_spsc_consumed << " messages in " << TEST_DURATION << " seconds\n";

    std::cout << "[Boost SPSC Queue] Produced: " << boost_produced << " messages in " << TEST_DURATION << " seconds\n";
    std::cout << "[Boost SPSC Queue] Consumed: " << boost_consumed << " messages in " << TEST_DURATION << " seconds\n";

    return 0;
}

