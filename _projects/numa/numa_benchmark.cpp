#define _GNU_SOURCE
#include <numa.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <cstring>
#include <sched.h>

constexpr size_t ARRAY_SIZE = 100 * 1024 * 1024; // 100 million elements (~800MB)
constexpr int NUM_TRIALS = 5;

// Function to bind a thread to a specific CPU
void bind_to_cpu(int cpu) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) != 0) {
        std::cerr << "Failed to set CPU affinity to CPU " << cpu << "\n";
    }
}

// Simulated NUMA benchmark: compute on one CPU, allocate memory on another
void benchmark(int compute_cpu, int memory_node, const char* description) {
    bind_to_cpu(compute_cpu);

    // Allocate memory on a specific NUMA node
    double* data = (double*)numa_alloc_onnode(ARRAY_SIZE * sizeof(double), memory_node);
    if (!data) {
        std::cerr << "Failed to allocate memory on NUMA node " << memory_node << "\n";
        return;
    }

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        data[i] = 1.0;
    }

    // Benchmark computation time
    double sum = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        sum = 0.0;
        for (size_t i = 0; i < ARRAY_SIZE; i++) {
            sum += data[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();

    std::cout << description << " (Compute on CPU " << compute_cpu << ", Memory Node " << memory_node << "): "
              << duration / NUM_TRIALS << " seconds\n";

    // Free allocated memory
    numa_free(data, ARRAY_SIZE * sizeof(double));
}

int main() {
    if (numa_available() < 0) {
        std::cerr << "NUMA not supported on this system.\n";
        return 1;
    }

    int num_nodes = numa_max_node() + 1;
    int num_cpus = numa_num_task_cpus();

    if (num_nodes < 1) {
        std::cerr << "Warning: This system only has 1 NUMA node. Using simulation.\n";
    }

    std::cout << "Detected " << num_nodes << " NUMA nodes and " << num_cpus << " CPUs.\n";

    int cpu1 = 0;           // Compute on CPU 0
    int cpu2 = num_cpus / 2; // Compute on a CPU further apart

    // Case 1: Compute and allocate on the same CPU
    benchmark(cpu1, 0, "Simulated NUMA-local execution");

    // Case 2: Compute on CPU2 but memory allocated near CPU1
    benchmark(cpu2, 0, "Simulated NUMA-remote execution");

    return 0;
}

