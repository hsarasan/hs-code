#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

void* threadFunction(void* arg) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset); // Bind the thread to CPU 0

    // Set the CPU affinity
    int result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        perror("pthread_setaffinity_np");
        return NULL;
    }

    printf("Thread running on CPU 0\n");

    // Simulate some work
    sleep(5);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);
    pthread_join(thread, NULL);
    return 0;
}