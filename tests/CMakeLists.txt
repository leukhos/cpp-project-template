add_executable(
    calculator_tests
    calculator.test.cpp
)

target_link_libraries(
    calculator_tests
    cpp_project_template
    gtest_main
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)