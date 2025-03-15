#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include "shm_ring_buffer.h"

int main() {
    // Open shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Map shared memory
    auto* ring = static_cast<RingBuffer*>(
        mmap(nullptr, sizeof(RingBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if (ring == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    while (true) {
        uint32_t head = ring->head.load(std::memory_order_acquire);
        uint32_t tail = ring->tail.load(std::memory_order_relaxed);

        // Check if the buffer is empty
        if (head == tail) {
            std::cout << "Buffer empty, waiting..." << std::endl;
            usleep(1000);
            continue;
        }

        // Read message
        char message[MESSAGE_SIZE];
        strncpy(message, ring->buffer[tail], MESSAGE_SIZE);
        message[MESSAGE_SIZE - 1] = '\0';  // Ensure null-termination

        // Move tail forward (using release to ensure data is read before moving)
        ring->tail.store((tail + 1) % BUFFER_SIZE, std::memory_order_release);

        std::cout << "Consumed: " << message << std::endl;
        usleep(70000);  // Simulate processing delay
    }

    return 0;
}

