#include <iostream>
#include <fcntl.h>      // For O_CREAT, O_RDWR
#include <sys/mman.h>   // For shared memory
#include <sys/stat.h>   // For mode constants
#include <unistd.h>     // For ftruncate, close
#include <semaphore.h>  // For semaphores
#include <cstring>      // For strcpy

#define SHM_NAME "/my_shm"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SHM_SIZE 1024

int main() {
    // Open existing shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    void* ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Open semaphores
    sem_t* sem_empty = sem_open(SEM_EMPTY, 0);
    sem_t* sem_full  = sem_open(SEM_FULL, 0);

    // Wait until there is data
    sem_wait(sem_full);

    // Read data from shared memory
    std::cout << "Consumer read: " << static_cast<char*>(ptr) << "\n";

    // Signal that memory is empty again
    sem_post(sem_empty);

    // Cleanup
    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    sem_close(sem_empty);
    sem_close(sem_full);

    return 0;
}

