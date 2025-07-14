find_package(benchmark REQUIRED)

add_executable(calculator_benchmarks)

target_sources(calculator_benchmarks
    PRIVATE
        calculator.benchmark.cpp
)

target_link_libraries(calculator_benchmarks
    PRIVATE
        calculator
        benchmark::benchmark
)
