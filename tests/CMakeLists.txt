find_package(GTest CONFIG REQUIRED)

add_executable(calculator-tests)
target_sources(calculator-tests
    PRIVATE
        main.cpp
        calculator.test.cpp
)

target_link_libraries(calculator-tests
    PRIVATE
        calculator
        project_warnings
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(calculator-tests)
