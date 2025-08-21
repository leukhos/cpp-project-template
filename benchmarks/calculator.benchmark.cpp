// First-party headers
#include "calculator/calculator.h"

// Third-party headers
#include <benchmark/benchmark.h>

static void BM_Calculator_Add_Basic(benchmark::State& state) {
  Calculator calculator;
  for (auto _ : state) {
    benchmark::DoNotOptimize(calculator.add(42, 17));
  }
}
BENCHMARK(BM_Calculator_Add_Basic);

static void BM_Calculator_Subtract_Basic(benchmark::State& state) {
  Calculator calculator;
  for (auto _ : state) {
    benchmark::DoNotOptimize(calculator.subtract(42, 17));
  }
}
BENCHMARK(BM_Calculator_Subtract_Basic);

static void BM_Calculator_Multiply_Basic(benchmark::State& state) {
  Calculator calculator;
  for (auto _ : state) {
    benchmark::DoNotOptimize(calculator.multiply(42, 17));
  }
}
BENCHMARK(BM_Calculator_Multiply_Basic);

static void BM_Calculator_Divide_Basic(benchmark::State& state) {
  Calculator calculator;
  for (auto _ : state) {
    benchmark::DoNotOptimize(calculator.divide(42, 17));
  }
}
BENCHMARK(BM_Calculator_Divide_Basic);

static void BM_Calculator_Add_Range(benchmark::State& state) {
  Calculator calculator;
  for (auto _ : state) {
    benchmark::DoNotOptimize(calculator.add(state.range(0), state.range(1)));
  }
}
BENCHMARK(BM_Calculator_Add_Range)->Args({8, 32})->Args({64, 128})->Args({512, 1024});

BENCHMARK_MAIN();