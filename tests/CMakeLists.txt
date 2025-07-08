include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release 1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test sources
file(GLOB TEST_SOURCES *.cpp *.h)

add_executable(${PROJECT_NAME}-tests ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}-tests
    ${PROJECT_NAME}
    gtest_main
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-tests)
