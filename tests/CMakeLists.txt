find_package(doctest REQUIRED)
find_package(trompeloeil REQUIRED)

add_executable(calculator_tests)

# Functional tests from tests/ directory
target_sources(calculator_tests
    PRIVATE
        calculator.test.cpp
)

# Unit tests embedded in source files (Rust-style)
# Compile source files WITHOUT DOCTEST_CONFIG_DISABLE to enable unit tests
# Note: The library build defines DOCTEST_CONFIG_DISABLE to strip tests from production code
target_sources(calculator_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/calculator.cpp
)

target_link_libraries(calculator_tests
    PRIVATE
        doctest::doctest
        trompeloeil::trompeloeil
)

# Include calculator headers for unit tests in source
target_include_directories(calculator_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

include(doctest)
doctest_discover_tests(calculator_tests)
