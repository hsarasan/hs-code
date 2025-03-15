#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <atomic>
#include <cstddef>

constexpr size_t BUFFER_SIZE = 1024;  // Must be a power of 2

template <typename T>
class RingBuffer {
public:
    std::atomic<size_t> head{0};  // Producer index
    std::atomic<size_t> tail{0};  // Consumer index
    T data[BUFFER_SIZE];          // Data array

    // Enqueue data into the buffer (Producer)
    bool enqueue(const T& value) {
        size_t current_head = head.load(std::memory_order_relaxed);
        size_t next_head = (current_head + 1) % BUFFER_SIZE;

        if (next_head == tail.load(std::memory_order_acquire)) {
            return false;  // Buffer is full
        }

        data[current_head] = value;
        head.store(next_head, std::memory_order_release);
        return true;
    }

    // Dequeue data from the buffer (Consumer)
    bool dequeue(T& value) {
        size_t current_tail = tail.load(std::memory_order_relaxed);
        if (current_tail == head.load(std::memory_order_acquire)) {
            return false;  // Buffer is empty
        }

        value = data[current_tail];
        tail.store((current_tail + 1) % BUFFER_SIZE, std::memory_order_release);
        return true;
    }

    // Check if the buffer is empty
    bool is_empty() const {
        return head.load(std::memory_order_acquire) == tail.load(std::memory_order_acquire);
    }

    // Check if the buffer is full
    bool is_full() const {
        return (head.load(std::memory_order_acquire) + 1) % BUFFER_SIZE == tail.load(std::memory_order_acquire);
    }
};

#endif  // RING_BUFFER_H

