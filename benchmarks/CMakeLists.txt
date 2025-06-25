add_executable(
    calculator_benchmarks
    calculator.benchmark.cpp
)

target_link_libraries(
    calculator_benchmarks
    cpp_project_template
    benchmark::benchmark
)