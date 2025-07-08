cmake_minimum_required(VERSION 3.28)
project(calculator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Gather source files (exclude main.cpp from library)
file(GLOB LIB_SOURCES src/*.cpp src/*.h include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include
    PRIVATE
        include/${PROJECT_NAME}
        src
)

# Testing
if(BUILD_TESTING)
    include(CTest)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release 1.17.0
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    # Test sources
    file(GLOB TEST_SOURCES tests/*.cpp tests/*.h)
    
    add_executable(${PROJECT_NAME}-tests ${TEST_SOURCES})
    
    target_link_libraries(${PROJECT_NAME}-tests
        ${PROJECT_NAME}
        gtest_main
        gmock_main
    )
    
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-tests)
endif()

# Benchmarks
option(BUILD_BENCHMARKS "Build benchmark executables" OFF)
if(BUILD_BENCHMARKS)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG eddb0241389718a23a42db6af5f0164b6e0139af # release 1.9.4
    )
    
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(benchmark)
    
    # Benchmark sources
    file(GLOB BENCHMARK_SOURCES benchmarks/*.cpp benchmarks/*.h)
    
    add_executable(calculator_benchmarks ${BENCHMARK_SOURCES})
    
    target_link_libraries(calculator_benchmarks
        cpp_project_template
        benchmark::benchmark
    )
endif()