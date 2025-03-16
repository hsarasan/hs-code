Program to simulate and test numa awareness

user@71collinsdrive:~/hs-code/_projects/numa$ ./numa_test 
Detected 12 CPUs, simulating NUMA effects.
Simulated NUMA-local execution (CPU 0): 0.389227 seconds
Simulated NUMA-remote execution (CPU 6): 0.577394 seconds




user@71collinsdrive:~/hs-code/_projects/numa$ sudo perf stat -e LLC-load-misses ./numa_test
Detected 12 CPUs, simulating NUMA effects.
Simulated NUMA-local execution (CPU 0): 0.39253 seconds
Simulated NUMA-remote execution (CPU 6): 0.577294 seconds

 Performance counter stats for './numa_test':

             2,517      cpu_atom/LLC-load-misses/                                               (57.55%)
           440,941      cpu_core/LLC-load-misses/                                               (42.45%)

       6.409625468 seconds time elapsed

       5.521340000 seconds user
       0.882734000 seconds sys



to build and run



make clean
make
make run
