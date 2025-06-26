cmake_minimum_required(VERSION 3.30)
project(cpp-project-template VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)
endif()

include(FetchContent)

# Gather source files (exclude main.cpp from library)
file(GLOB LIB_SOURCES src/*.cpp src/*.h include/*.h)
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# Main library
add_library(cpp_project_template ${LIB_SOURCES})

target_include_directories(cpp_project_template
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Main executable
add_executable(main src/main.cpp)
target_link_libraries(main cpp_project_template)

# Testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release 1.17.0
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    # Test sources
    file(GLOB TEST_SOURCES tests/*.cpp tests/*.h)
    
    add_executable(calculator_tests ${TEST_SOURCES})
    
    target_link_libraries(calculator_tests
        cpp_project_template
        gtest_main
        gmock_main
    )
    
    include(GoogleTest)
    gtest_discover_tests(calculator_tests)
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