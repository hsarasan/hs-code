#ifndef SPSC_H_
#define SPSC_H_

#include <atomic>
#include <vector>
#include <iostream>

template <typename T>
class SPSCQueue {
private:
    alignas(64) std::vector<T> buffer;  // Cache-friendly
    alignas(64) std::atomic<size_t> tail{0}; // Consumer index
    alignas(64) std::atomic<size_t> head{0}; // Producer index
    const size_t capacity;

public:
    explicit SPSCQueue(size_t cap) : buffer(cap), capacity(cap+1) {}

    bool enqueue(const T& item) {
        size_t h = head.load(std::memory_order_relaxed);
        size_t next = (h + 1) % capacity;
        
        if (next == tail.load(std::memory_order_acquire)) {
            return false; // Queue is full
        }
        
        buffer[h] = item;
        head.store(next, std::memory_order_release);
        return true;
    }

    bool dequeue(T& item) {
        size_t t = tail.load(std::memory_order_relaxed);

        if (t == head.load(std::memory_order_acquire)) {
            return false; // Queue is empty
        }

        item = buffer[t];
        tail.store((t + 1) % capacity, std::memory_order_release);
        return true;
    }
};

#endif