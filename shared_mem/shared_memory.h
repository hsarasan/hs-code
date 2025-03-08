#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <semaphore.h>

#define SHM_NAME "/shm_ring_buffer"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"

#define BUFFER_SIZE 5   // Number of messages in the circular buffer
#define MESSAGE_SIZE 256 // Max length of each message

struct SharedMemory {
    char buffer[BUFFER_SIZE][MESSAGE_SIZE];  // Circular buffer
    int write_pos;  // Index for producer
    int read_pos;   // Index for consumer
};

#endif

