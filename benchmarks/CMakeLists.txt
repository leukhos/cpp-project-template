include(FetchContent)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG eddb0241389718a23a42db6af5f0164b6e0139af # release 1.9.4
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

add_executable(calculator-benchmarks)

target_sources(calculator-benchmarks
    PRIVATE
        calculator.benchmark.cpp
)

target_link_libraries(calculator-benchmarks
    PRIVATE
        calculator
        project_warnings
        benchmark::benchmark
)
