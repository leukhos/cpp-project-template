cmake_minimum_required(VERSION 3.23)
project(calculator)

add_subdirectory(src)

option(CALCULATOR_BUILD_TESTS "Build tests for the calculator library" OFF)
if(CALCULATOR_BUILD_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()

option(CALCULATOR_BUILD_BENCHMARKS "Build benchmark executables" OFF)
if(CALCULATOR_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()