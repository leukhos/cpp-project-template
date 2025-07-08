cmake_minimum_required(VERSION 3.28)
project(calculator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files (exclude main.cpp from library)
file(GLOB LIB_SOURCES src/*.cpp src/*.h include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()

    option(ENABLE_BENCHMARKS "Build benchmark executables" OFF)
    if(ENABLE_BENCHMARKS)
        add_subdirectory(benchmarks)
    endif()
endif()