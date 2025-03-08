#include <iostream>
#include <fcntl.h>      // For O_CREAT, O_RDWR
#include <sys/mman.h>   // For shared memory functions
#include <sys/stat.h>   // For mode constants
#include <unistd.h>     // For ftruncate, close
#include <cstring>   


#define SHM_NAME "/my_shm"
#define SHM_SIZE 1024

int main() {
    // Open existing shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory\n";
        return 1;
    }

    // Map shared memory
    void* ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Memory mapping failed\n";
        return 1;
    }

    // Read data
    std::cout << "Consumer read: " << static_cast<char*>(ptr) << "\n";

    // Cleanup
    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    return 0;
}

