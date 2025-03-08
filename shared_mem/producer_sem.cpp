#include <iostream>
#include <fcntl.h>      // For O_CREAT, O_RDWR
#include <sys/mman.h>   // For shared memory
#include <sys/stat.h>   // For mode constants
#include <unistd.h>     // For ftruncate, close
#include <cstring>      // For memcpy
#include <semaphore.h>  // For semaphores

#define SHM_NAME "/my_shm"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SHM_SIZE 1024

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Create semaphores
    sem_t* sem_empty = sem_open(SEM_EMPTY, O_CREAT, 0666, 1);  // Start as 1 (empty)
    sem_t* sem_full  = sem_open(SEM_FULL, O_CREAT, 0666, 0);   // Start as 0 (empty)

    // Wait until memory is empty
    sem_wait(sem_empty);

    // Write to shared memory
    const char* message = "Hello from Producer!";
    memcpy(ptr, message, strlen(message) + 1);
    std::cout << "Producer wrote: " << message << "\n";

    // Signal that data is available
    sem_post(sem_full);

    // Keep the process running (for demonstration)
    std::cout << "Press Enter to exit...\n";
    std::cin.get();



    // Cleanup
    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(sem_empty);
    sem_close(sem_full);
    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);

    return 0;
}

