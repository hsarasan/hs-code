#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>
#include "shared_memory.h"

int main() {
    // Open shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedMemory));
    SharedMemory* shm = (SharedMemory*) mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize shared memory (only needed the first time)
    shm->write_pos = 0;
    shm->read_pos = 0;

    // Open semaphores
    sem_t* sem_empty = sem_open(SEM_EMPTY, O_CREAT, 0666, BUFFER_SIZE);
    sem_t* sem_full  = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t* sem_mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    std::string messages[] = {"Msg1", "Msg2", "Msg3", "Msg4", "Msg5", "Msg6"};

    for (const std::string& msg : messages) {
        sem_wait(sem_empty);  // Wait for an empty slot
        sem_wait(sem_mutex);  // Lock access to shared memory

        // Write message to shared memory
        strncpy(shm->buffer[shm->write_pos], msg.c_str(), MESSAGE_SIZE);
        std::cout << "Producer wrote: " << msg << " at position " << shm->write_pos << "\n";

        // Move write position forward
        shm->write_pos = (shm->write_pos + 1) % BUFFER_SIZE;

        sem_post(sem_mutex);  // Unlock shared memory
        sem_post(sem_full);   // Signal that a message is available
        sleep(1);             // Simulate delay
    }

    // Cleanup
    munmap(shm, sizeof(SharedMemory));
    close(shm_fd);
    return 0;
}
