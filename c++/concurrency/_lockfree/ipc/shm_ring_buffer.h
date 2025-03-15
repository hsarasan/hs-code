#ifndef SHM_RING_BUFFER_H
#define SHM_RING_BUFFER_H

#include <atomic>
#include <cstdint>

constexpr int BUFFER_SIZE = 256;  // Number of slots in the ring buffer
constexpr int MESSAGE_SIZE = 64;  // Size of each message in bytes
constexpr const char* SHM_NAME = "/shm_ring_buffer";

struct RingBuffer {
    std::atomic<uint32_t> head{0};  // Write index
    std::atomic<uint32_t> tail{0};  // Read index
    char buffer[BUFFER_SIZE][MESSAGE_SIZE];  // Fixed-size buffer slots
};

#endif  // SHM_RING_BUFFER_H

