
#include <iostream>
#include <thread>
#include "shared_memory.h"

constexpr size_t NUM_MESSAGES = 10000;

void producer(RingBuffer<int>& buffer) {
    for (size_t i = 0; i < NUM_MESSAGES; ++i) {
        while (!buffer.enqueue(i)) {
            std::this_thread::yield();  // Wait if full
        }
        std::cout << "Produced: " << i << std::endl;
    }
}

int main() {
    SharedMemoryWrapper<int> shm(true);  // Create shared memory
    RingBuffer<int>* buffer = shm.get_buffer();

    producer(*buffer);
    return 0;
}

