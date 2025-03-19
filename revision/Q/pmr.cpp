#include <iostream>
#include <memory_resource>
#include <vector>

int main() {
    // Stack-allocated buffer (1KB)
    constexpr size_t bufferSize = 1024;
    alignas(std::max_align_t) char buffer[bufferSize];

    // Create a monotonic buffer resource using the stack buffer
    std::pmr::monotonic_buffer_resource pool(buffer, bufferSize);

    // Create a pmr::vector using the custom memory resource
    std::pmr::vector<int> vec(&pool);

    // Insert elements
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    // Print values
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // No explicit deallocation needed
    return 0;
}
