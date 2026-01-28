find_package(doctest REQUIRED)
find_package(trompeloeil REQUIRED)

add_executable(calculator_tests)
target_sources(calculator_tests
    PRIVATE
        main.cpp
        calculator.test.cpp
)

target_link_libraries(calculator_tests
    PRIVATE
        calculator
        doctest::doctest 
        trompeloeil::trompeloeil
)

include(doctest)
doctest_discover_tests(calculator_tests)