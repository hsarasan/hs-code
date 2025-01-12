#include <bits/stdc++.h>

int main() {
    // Use a monotonic_buffer_resource for efficient memory allocation
    char buffer[1024];
    std::pmr::monotonic_buffer_resource pool(buffer, sizeof(buffer));

    // Create a vector using the monotonic buffer
    std::pmr::vector<int> vec(&pool);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (int i : vec) {
        std::cout << i << " ";
    }

    // No need to manually deallocate, as the buffer is automatically reclaimed
}