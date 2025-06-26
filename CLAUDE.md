# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is a C++ project template repository that provides a modern C++ project structure with CMake build system, GoogleTest/GoogleMock testing framework, and Google Benchmark performance testing. The template includes example code demonstrating best practices and proper project organization.

## C++ Guidelines

See [docs/naming_conventions.md](docs/naming_conventions.md) for detailed naming conventions.

See [docs/code_guidelines.md](docs/code_guidelines.md) for code formatting and header inclusion rules.

## Current Status
The project template is fully implemented with:
- CMake 3.30+ build system with FetchContent dependency management
- GoogleTest v1.17.0 and GoogleMock testing framework
- Google Benchmark v1.9.4 performance testing
- C++20 standard with modern language features
- Example Calculator class demonstrating the structure

## Project Structure
The template includes:
- `src/` - Source code directory with Calculator implementation
- `include/` - Header files
- `tests/` - Unit tests with GoogleTest/GoogleMock
- `benchmarks/` - Performance benchmarks with Google Benchmark
- `docs/` - Code guidelines and naming conventions
- `CMakeLists.txt` - Main CMake configuration
- `cmake/` - CMake modules and utilities

## Build Commands
The CMake build system is fully configured:

### Basic Build
```bash
mkdir build && cd build
cmake ..
make
```

### With Tests
```bash
cmake .. -DBUILD_TESTING=ON
make
```

### With Benchmarks
```bash
cmake .. -DBUILD_BENCHMARKS=ON
make
```

## Testing
Testing framework is fully implemented with GoogleTest/GoogleMock:

```bash
make test
# or
ctest
# or run directly
./tests/calculator_test
```

### Test Naming Convention
Tests follow: `MethodName_Scenario_ExpectedBehavior`
- Example: `Add_PositiveNumbers_ReturnsCorrectSum`

### Test Structure
All tests use AAA pattern:
- **Arrange**: Set up test data
- **Act**: Execute the method
- **Assert**: Verify expected outcome

## Benchmarking
Benchmarking framework is implemented with Google Benchmark:

```bash
./benchmarks/calculator_benchmark
```

### Benchmark Naming Convention
Benchmarks follow: `BM_DescriptiveName`
- Example: `BM_Addition`, `BM_LargeVectorSort`

## Code Quality
- **clang-format**: Microsoft style formatting
- **Header organization**: Strict ordering rules (see code_guidelines.md)
- **Compiler warnings**: Comprehensive warning configuration
- **Naming conventions**: Strict C++ naming standards

## Important Instructions for Claude

### MANDATORY Requirements
1. **Always run clang-format** before code changes:
   ```bash
   clang-format -i src/**/*.{cpp,h} include/**/*.h tests/**/*.cpp
   ```

2. **Follow header inclusion order**:
   - Precompiled headers
   - First-party headers  
   - Third-party headers
   - Standard library headers

3. **Use required prefixes**:
   - Class members: `m_camelCase`
   - Static members: `s_camelCase`
   - Global variables: `g_camelCase`

4. **Test naming**: `MethodName_Scenario_ExpectedBehavior`
5. **Benchmark naming**: `BM_DescriptiveName`
6. **File naming**: PascalCase class → snake_case files

## Development Notes
- Uses MIT License
- Standard C++ .gitignore configured
- **C++20 standard** with modern CMake 3.30+
- Automatic dependency management with FetchContent
- GoogleTest v1.17.0, Google Benchmark v1.9.4
- Compatible with GCC 10+, Clang 10+, MSVC 2019+