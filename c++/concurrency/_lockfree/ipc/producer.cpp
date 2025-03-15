#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include "shm_ring_buffer.h"

int main() {
    // Open or create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // Set shared memory size
    if (ftruncate(shm_fd, sizeof(RingBuffer)) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    // Map shared memory
    auto* ring = static_cast<RingBuffer*>(
        mmap(nullptr, sizeof(RingBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if (ring == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Ensure ring buffer is initialized properly
    if (ring->head.load(std::memory_order_relaxed) > BUFFER_SIZE || 
        ring->tail.load(std::memory_order_relaxed) > BUFFER_SIZE) {
        std::cout << "Resetting ring buffer" << std::endl;
        ring->head.store(0, std::memory_order_relaxed);
        ring->tail.store(0, std::memory_order_relaxed);
    }

    int message_count = 0;
    while (true) {
        uint32_t head = ring->head.load(std::memory_order_relaxed);
        uint32_t tail = ring->tail.load(std::memory_order_acquire);

        // Check for buffer overflow
        if ((head + 1) % BUFFER_SIZE == tail) {
            std::cerr << "Buffer full, waiting..." << std::endl;
            usleep(1000);
            continue;
        }

        // Create message
        char message[MESSAGE_SIZE];
        snprintf(message, MESSAGE_SIZE, "Message %d", message_count++);

        // Copy data safely
        strncpy(ring->buffer[head], message, MESSAGE_SIZE - 1);
        ring->buffer[head][MESSAGE_SIZE - 1] = '\0';  // Null-terminate for safety

        // Update head pointer
        ring->head.store((head + 1) % BUFFER_SIZE, std::memory_order_release);

        std::cout << "Produced: " << message << std::endl;
        usleep(50000);  // Simulate delay
    }

    return 0;
}

