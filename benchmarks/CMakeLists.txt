include(FetchContent)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG eddb0241389718a23a42db6af5f0164b6e0139af # release 1.9.4
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

# Benchmark sources
file(GLOB BENCHMARK_SOURCES benchmarks/*.cpp benchmarks/*.h)

add_executable(${PROJECT_NAME}-benchmarks ${BENCHMARK_SOURCES})

target_link_libraries(${PROJECT_NAME}-benchmarks
    ${PROJECT_NAME}
    benchmark::benchmark
)
