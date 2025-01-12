//https://quick-bench.com/q/JNMxVIK1jhNJkcxtjd9Pz1IqVyI

#include <iostream>
#include <vector>

using namespace std;

template <int n>
struct fib_tmp{
  static const int value=fib_tmp<n-1>::value +fib_tmp<n-2>::value;
};
template <>
struct fib_tmp<1>{
    static const int value=1;
};
template <>
struct fib_tmp<0>{
    static const int value=0;
};

int fib_dp(int n){
    vector<int> dp(n+1,0);
    dp[1]=1;
    for (int i=2;i<n+1;++i){
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

int fib_recursion(int n){
    if (n==0) return 0;
    if (n==1) return 1;
    return fib_recursion(n-1)+fib_recursion(n-2);
}


static void fib_tmp_fn(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    int n=fib_tmp<10>::value;
  }
}
// Register the function as a benchmark
BENCHMARK(fib_tmp_fn);

static void fib_dp_fn(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    int n=fib_dp(10);
  }
}
// Register the function as a benchmark
BENCHMARK(fib_dp_fn);

static void fib_recursion_fn(benchmark::State& state) {
  // Code before the loop is not measured

  for (auto _ : state) {
    int n=fib_recursion(10);
  }
}
BENCHMARK(fib_recursion_fn);
