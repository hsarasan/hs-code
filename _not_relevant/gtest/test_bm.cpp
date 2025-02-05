#include <benchmark/benchmark.h>

static void BM_Simple(benchmark::State& state) {
    for (auto _ : state) {
        // Simple benchmark task
    }
}
BENCHMARK(BM_Simple);

BENCHMARK_MAIN();
