#include "spsc.h"

using namespace std;


int main() {
    SPSCQueue<int> queue(10); // Queue with capacity 10

    // Producer thread
    for (int i = 0; i < 10; ++i) {
        while (!queue.enqueue(i)) {
            // Queue is full, retry or handle accordingly
        }
        std::cout << "Enqueued: " << i << std::endl;
    }

    // Consumer thread
    int item;
    for (int i = 0; i < 10; ++i) {
        while (!queue.dequeue(item)) {
            // Queue is empty, retry or handle accordingly
        }
        std::cout << "Dequeued: " << item << std::endl;
    }

    return 0;
}