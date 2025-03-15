spinlock with atomic flag

perf_test => with a low number of threads, spinlock performs badly
but as the thread counts increases spinlock gets better
probably because more context switching happens (vs contention) with higher number of threads