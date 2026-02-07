add_library(calculator)
add_library(calculator::calculator ALIAS calculator)

target_sources(calculator
    PUBLIC
        FILE_SET calculator_headers
        TYPE HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include
        FILES
            ${CMAKE_SOURCE_DIR}/include/calculator/calculator.h
    PRIVATE
        calculator.cpp
)

target_compile_features(calculator PUBLIC cxx_std_20)

install(
    TARGETS calculator
    EXPORT calculatorTargets
    FILE_SET calculator_headers
)

install(
    EXPORT calculatorTargets
    DESTINATION share/cmake/calculator
    NAMESPACE calculator::
)

install(
    FILES
        ${CMAKE_SOURCE_DIR}/cmake/calculatorConfig.cmake
    DESTINATION
        share/cmake/calculator
)