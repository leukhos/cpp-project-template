#include "calculator.h"

#include <benchmark/benchmark.h>

static void BM_Addition(benchmark::State& state)
{
    Calculator calc;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(calc.add(42, 17));
    }
}
BENCHMARK(BM_Addition);

static void BM_Subtraction(benchmark::State& state)
{
    Calculator calc;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(calc.subtract(42, 17));
    }
}
BENCHMARK(BM_Subtraction);

static void BM_Multiplication(benchmark::State& state)
{
    Calculator calc;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(calc.multiply(42, 17));
    }
}
BENCHMARK(BM_Multiplication);

static void BM_Division(benchmark::State& state)
{
    Calculator calc;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(calc.divide(42, 17));
    }
}
BENCHMARK(BM_Division);

static void BM_AdditionRange(benchmark::State& state)
{
    Calculator calc;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(calc.add(state.range(0), state.range(1)));
    }
}
BENCHMARK(BM_AdditionRange)->Args({8, 32})->Args({64, 128})->Args({512, 1024});

BENCHMARK_MAIN();