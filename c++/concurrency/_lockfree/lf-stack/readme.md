Lock free stack implemented with a linked list

Benchmark results

=== Benchmarking with 1 threads ===
Lock-Free Stack Push (1 threads): 6.55904e+06 ops/sec (0.0152461 sec)
Lock-Free Stack Pop (1 threads): 9.64499e+06 ops/sec (0.0103681 sec)
Mutex-Based Stack Push (1 threads): 9.27612e+06 ops/sec (0.0107804 sec)
Mutex-Based Stack Pop (1 threads): 6.48598e+06 ops/sec (0.0154179 sec)

=== Benchmarking with 2 threads ===
Lock-Free Stack Push (2 threads): 6.22375e+06 ops/sec (0.032135 sec)
Lock-Free Stack Pop (2 threads): 3.51885e+06 ops/sec (0.0568367 sec)
Mutex-Based Stack Push (2 threads): 2.79725e+06 ops/sec (0.0714989 sec)
Mutex-Based Stack Pop (2 threads): 2.63687e+06 ops/sec (0.0758475 sec)

=== Benchmarking with 4 threads ===
Lock-Free Stack Push (4 threads): 5.23059e+06 ops/sec (0.0764732 sec)
Lock-Free Stack Pop (4 threads): -355468 ops/sec (-1.12528 sec)
Mutex-Based Stack Push (4 threads): 2.36785e+06 ops/sec (0.16893 sec)
Mutex-Based Stack Pop (4 threads): 1.88977e+06 ops/sec (0.211665 sec)

=== Benchmarking with 8 threads ===
Lock-Free Stack Push (8 threads): 4.36336e+06 ops/sec (0.183345 sec)
Lock-Free Stack Pop (8 threads): 2.36801e+06 ops/sec (0.337836 sec)
Mutex-Based Stack Push (8 threads): 1.36285e+06 ops/sec (0.587006 sec)
Mutex-Based Stack Pop (8 threads): 1.09774e+06 ops/sec (0.72877 sec)

=== Benchmarking with 16 threads ===
Lock-Free Stack Push (16 threads): 4.01972e+06 ops/sec (0.398038 sec)
Lock-Free Stack Pop (16 threads): 2.26918e+06 ops/sec (0.705101 sec)
Mutex-Based Stack Push (16 threads): 1.23524e+06 ops/sec (1.29529 sec)
Mutex-Based Stack Pop (16 threads): 978669 ops/sec (1.63487 sec)

=== Benchmarking with 32 threads ===
Lock-Free Stack Push (32 threads): 3.82281e+06 ops/sec (0.83708 sec)
Lock-Free Stack Pop (32 threads): 2.17057e+06 ops/sec (1.47427 sec)
Mutex-Based Stack Push (32 threads): 1.32206e+06 ops/sec (2.42047 sec)
Mutex-Based Stack Pop (32 threads): 1.05348e+06 ops/sec (3.03754 sec)

=== Benchmarking with 64 threads ===
Lock-Free Stack Push (64 threads): 4.1947e+06 ops/sec (1.52574 sec)
Lock-Free Stack Pop (64 threads): 2.16422e+06 ops/sec (2.95718 sec)
Mutex-Based Stack Push (64 threads): 1.25674e+06 ops/sec (5.09256 sec)
Mutex-Based Stack Pop (64 threads): 1.03837e+06 ops/sec (6.1635 sec)

=== Benchmarking with 128 threads ===
Lock-Free Stack Push (128 threads): 4.21287e+06 ops/sec (3.03831 sec)
Lock-Free Stack Pop (128 threads): 2.18584e+06 ops/sec (5.85587 sec)
Mutex-Based Stack Push (128 threads): 1.2046e+06 ops/sec (10.6259 sec)
Mutex-Based Stack Pop (128 threads): 1.03272e+06 ops/sec (12.3944 sec)

