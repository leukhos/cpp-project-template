find_package(GTest REQUIRED)

add_executable(calculator_tests)
target_sources(calculator_tests
    PRIVATE
        main.cpp
        calculator.test.cpp
)

target_link_libraries(calculator_tests
    PRIVATE
        calculator
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)
