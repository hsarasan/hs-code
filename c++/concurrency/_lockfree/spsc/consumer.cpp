#include <iostream>
#include <thread>
#include "shared_memory.h"

constexpr size_t NUM_MESSAGES = 10000;

void consumer(RingBuffer<int>& buffer) {
    int value;
    for (size_t i = 0; i < NUM_MESSAGES; ++i) {
        while (!buffer.dequeue(value)) {
            std::this_thread::yield();  // Wait if empty
        }
        std::cout << "Consumed: " << value << std::endl;
    }
}

int main() {
    SharedMemoryWrapper<int> shm(false);  // Attach to existing shared memory
    RingBuffer<int>* buffer = shm.get_buffer();

    consumer(*buffer);
    return 0;
}

