cmake_minimum_required(VERSION 3.30)
project(calculator)

option(CALCULATOR_ENABLE_TEST "Enable testing" OFF)
option(CALCULATOR_ENABLE_BENCH "Enable benchmarking" OFF)

add_subdirectory(src)

if(CALCULATOR_ENABLE_TEST)
    include(CTest)
    add_subdirectory(tests)
endif()

if(CALCULATOR_ENABLE_BENCH)
    add_subdirectory(benches)
endif()