#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "ring_buffer.h"

constexpr const char* SHM_NAME = "/shm_ring_buffer";

template <typename T>
class SharedMemoryWrapper {
private:
    int shm_fd;
    bool is_owner;
    RingBuffer<T>* buffer;

public:
    SharedMemoryWrapper(bool create = false) {
        if (create) {
            // Create and allocate shared memory
            shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
            ftruncate(shm_fd, sizeof(RingBuffer<T>));
            is_owner = true;
        } else {
            // Open existing shared memory
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
            is_owner = false;
        }

        if (shm_fd == -1) {
            perror("shm_open failed");
            exit(1);
        }

        // Map shared memory
        buffer = static_cast<RingBuffer<T>*>(
            mmap(nullptr, sizeof(RingBuffer<T>), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
        );

        if (buffer == MAP_FAILED) {
            perror("mmap failed");
            exit(1);
        }

        // Initialize only if we are the creator
        if (is_owner) {
            new (buffer) RingBuffer<T>();  // Placement new to construct in shared memory
        }
    }

    ~SharedMemoryWrapper() {
        munmap(buffer, sizeof(RingBuffer<T>));
        close(shm_fd);
        if (is_owner) {
            shm_unlink(SHM_NAME);
        }
    }

    RingBuffer<T>* get_buffer() {
        return buffer;
    }
};

#endif  // SHARED_MEMORY_H

