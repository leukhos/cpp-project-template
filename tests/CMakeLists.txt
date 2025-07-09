find_package(GTest CONFIG REQUIRED)

file(GLOB TEST_SOURCES *.cpp *.h)
add_executable(${PROJECT_NAME}-tests ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}-tests
    PRIVATE
        ${PROJECT_NAME}
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-tests)
