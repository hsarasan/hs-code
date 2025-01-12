#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdint>
;

class CustomMemoryManager {
public:
    // Allocate memory with alignment
    void* allocate(size_t size, size_t alignment) {
        void* ptr = nullptr;
        #ifdef __LINUX__
        if (posix_memalign(&ptr, alignment, size) != 0) {
            throw std::bad_alloc();
        }
        #else
        ptr = _aligned_malloc(size, alignment);
        #endif
        std::cout<<"Allocating "<<ptr<<std::endl;
        return ptr;
    }

    // Deallocate memory
    void deallocate(void* ptr) {
        std::cout<<"Freeing "<<ptr<<std::endl;   
        free(ptr);
             
    }

};

// Overloading global new and delete operators
void* operator new(size_t size) {

    return CustomMemoryManager().allocate(size, alignof(std::max_align_t));
}

void* operator new[](size_t size) {
    return CustomMemoryManager().allocate(size, alignof(std::max_align_t));
}

void operator delete(void* ptr)  noexcept {
    CustomMemoryManager().deallocate(ptr);
}

void operator delete[](void* ptr) noexcept {
    CustomMemoryManager().deallocate(ptr);
}

int main(){
    int* p = new int;
    int* arr = new int[5];

    std::cout << "p: " << p << std::endl;
    std::cout << "arr: " << arr << std::endl;

    delete p;

    return 0;
}

