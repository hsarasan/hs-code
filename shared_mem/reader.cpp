#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <cstring>
#include "shared_memory.h"

int main() {
    // Open shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    SharedMemory* shm = (SharedMemory*) mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Open semaphores
    sem_t* sem_empty = sem_open(SEM_EMPTY, 0);
    sem_t* sem_full  = sem_open(SEM_FULL, 0);
    sem_t* sem_mutex = sem_open(SEM_MUTEX, 0);

    for (int i = 0; i < 6; ++i) {
        sem_wait(sem_full);   // Wait until there's data
        sem_wait(sem_mutex);  // Lock access to shared memory

        // Read message from shared memory
        std::cout << "Consumer read: " << shm->buffer[shm->read_pos] << " from position " << shm->read_pos << "\n";

        // Move read position forward
        shm->read_pos = (shm->read_pos + 1) % BUFFER_SIZE;

        sem_post(sem_mutex);  // Unlock shared memory
        sem_post(sem_empty);  // Signal that a slot is free
        sleep(2);             // Simulate processing delay
    }

    // Cleanup
    munmap(shm, sizeof(SharedMemory));
    close(shm_fd);
    return 0;
}

