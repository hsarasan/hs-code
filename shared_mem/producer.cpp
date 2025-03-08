#include <iostream>
#include <fcntl.h>      // For O_CREAT, O_RDWR
#include <sys/mman.h>   // For shared memory functions
#include <sys/stat.h>   // For mode constants
#include <unistd.h>     // For ftruncate, close
#include <cstring>   

#define SHM_NAME "/my_shm"
#define SHM_SIZE 1024

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to create shared memory\n";
        return 1;
    }

    // Set size of shared memory
    ftruncate(shm_fd, SHM_SIZE);

    // Map shared memory
    void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Memory mapping failed\n";
        return 1;
    }

    // Write data to shared memory
    const char* message = "Hello from Producer!";
    memcpy(ptr, message, strlen(message) + 1);

    std::cout << "Producer wrote: " << message << "\n";

    // Keep the process running (for demonstration)
    std::cout << "Press Enter to exit...\n";
    std::cin.get();

    // Cleanup
    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);  // Remove shared memory
    return 0;
}

