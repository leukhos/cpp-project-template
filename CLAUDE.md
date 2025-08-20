# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Development Commands

### Building
```bash
# Configure with CMake presets (recommended)
cmake --preset gcc          # GCC compiler with vcpkg
cmake --preset clang        # Clang compiler with vcpkg  
cmake --preset msvc         # MSVC compiler (Windows only)

# Build the project
cmake --build build

# Alternative manual build
mkdir build && cd build
cmake .. -DCALCULATOR_BUILD_TESTS=ON
make
```

### Testing
```bash
# Run all tests
cmake --build build --target test
# or
cd build && ctest
# or run test executable directly
./build/tests/calculator_tests
```

### Benchmarks
```bash
# Configure with benchmarks enabled
cmake .. -DCALCULATOR_BUILD_BENCHMARKS=ON
cmake --build build
./build/benchmarks/calculator_benchmark
```

### Code Formatting
```bash
# Format all source files (MANDATORY before commits)
clang-format -i src/**/*.{cpp,h} include/**/*.h tests/**/*.cpp
```

## Project Architecture

### Build System
- **CMake 3.25+** with modern target-based configuration
- **vcpkg** for dependency management via `vcpkg.json`
- **CMake presets** for different compiler configurations (GCC, Clang, MSVC)
- **CMake FILE_SET** for modern header management

### Directory Structure
```
src/
├── CMakeLists.txt              # Library target definition
├── include/calculator/         # Public headers (using FILE_SET)
│   └── calculator.h           # Main header
├── calculator.cpp             # Implementation
└── cmake/calculatorConfig.cmake # Package config for installation

tests/
├── CMakeLists.txt             # Test executable setup
├── main.cpp                   # Test runner
└── calculator.test.cpp        # Unit tests

benchmarks/
├── CMakeLists.txt             # Benchmark executable setup
└── calculator.benchmark.cpp   # Performance tests
```

### Target Architecture
- **Main library**: `calculator` (aliased as `calculator::calculator`)
- **Test executable**: `calculator_tests` with GoogleTest/GoogleMock
- **Benchmark executable**: Uses Google Benchmark
- **C++20 standard** with comprehensive compiler warnings

## Coding Standards

### Critical Requirements
1. **Header organization** (MANDATORY order):
   ```cpp
   // First-party headers
   #include "calculator.h"
   
   // Third-party headers  
   #include <gtest/gtest.h>
   
   // Standard library headers
   #include <iostream>
   ```

2. **Naming conventions**:
   - Classes: `PascalCase` (Calculator, DataProcessor)
   - Variables/Functions: `camelCase` (processData, fileName)
   - Member variables: `m_camelCase` (m_result, m_isValid)
   - Static members: `s_camelCase` (s_instanceCount)
   - Files: `snake_case` (calculator.h, data_processor.cpp)

3. **Test naming**: `MethodName_Scenario_ExpectedBehavior`
   ```cpp
   TEST_F(CalculatorTest, Add_PositiveNumbers_ReturnsCorrectSum)
   ```

4. **AAA pattern for tests** with explicit comments:
   ```cpp
   // Arrange
   // Act  
   // Assert
   ```

5. **Assertions**: Use `EXPECT_THAT` with matchers instead of legacy macros:
   ```cpp
   EXPECT_THAT(result, Eq(expected));
   EXPECT_THAT([&]() { return calc.divide(10, 0); }, Throws<std::invalid_argument>());
   ```

6. **Benchmark naming**: `BM_DescriptiveName` format

### Dependencies
- **GoogleTest/GoogleMock**: Testing framework (vcpkg: gtest)
- **Google Benchmark**: Performance testing (vcpkg: benchmark)
- Dependencies managed through vcpkg features in `vcpkg.json`

## CMake Configuration Variables
- `CALCULATOR_BUILD_TESTS`: Enable/disable tests (ON by default)
- `CALCULATOR_BUILD_BENCHMARKS`: Enable/disable benchmarks (OFF by default)
- `VCPKG_MANIFEST_FEATURES`: Set to "tests" or "benchmarks" to pull dependencies

## Important Notes
- Always run `clang-format` before committing
- Use vcpkg toolchain file via CMake presets
- Follow strict header inclusion order with group comments
- All member variables must use `m_` prefix
- Exception classes must end with "Exception"
- Interface classes must start with "I"