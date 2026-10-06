#include <atomic>
#include <iostream>
#include <thread>

int main() {
    constexpr int item_count = 10;
    int counter = 0;
    std::atomic<bool> ready{false};

    std::jthread producer([&] {
        for (int value = 1; value <= item_count; ++value) {
            while (ready.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }

            counter = value;
            ready.store(true, std::memory_order_release);
        }
    });

    std::jthread consumer([&] {
        for (int i = 0; i < item_count; ++i) {
            while (!ready.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }

            std::cout << counter << '\n';
            ready.store(false, std::memory_order_release);
        }
    });
}
