cmake_minimum_required(VERSION 3.23)
project(calculator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

# Create interface library for project-wide compiler warnings
include(cmake/CompilerWarnings.cmake)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

add_library(calculator)

target_sources(calculator
    PRIVATE
        src/calculator.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/calculator/calculator.h
)

target_link_libraries(calculator PRIVATE project_warnings)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

option(ENABLE_BENCHMARKS "Build benchmark executables" OFF)
if(ENABLE_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()