# C++ Project Template

A modern C++ project template with CMake build system, GoogleTest/GoogleMock testing framework, and Google Benchmark performance testing.

## Todo
- Add some compiler warning setup
- Add a devcontainer
- Update the documentation, with a CLAUDE.md template
- Consider function defined for testing purpose only
- Review testing mechanism (for multi-project cases)
- Limit gtest to test with `VCPKG_MANIFEST_FEATURES`

## Features

- **CMake Build System**: Modern CMake (3.14+) with proper target-based configuration
- **Testing**: GoogleTest and GoogleMock integration with automatic test discovery
- **Benchmarking**: Google Benchmark for performance testing
- **Dependencies**: Automatic dependency management using CMake FetchContent
- **Modern C++**: C++20 standard with comprehensive compiler warnings

## Project Structure

```
cpp-project-template/
├── CMakeLists.txt          # Main CMake configuration
├── src/                    # Source files
│   ├── CMakeLists.txt
│   ├── calculator.cpp      # Example implementation
│   └── main.cpp           # Example main executable
├── include/                # Header files
│   └── calculator.h       # Example header
├── tests/                  # Unit tests
│   ├── CMakeLists.txt
│   └── calculator.test.cpp # Example GoogleTest/GoogleMock tests
├── benchmarks/             # Performance benchmarks
│   ├── CMakeLists.txt
│   └── calculator.benchmark.cpp # Example Google Benchmark tests
├── docs/                   # Documentation
│   ├── code_guidelines.md  # Coding standards and formatting rules
│   └── naming_conventions.md # Naming convention guidelines
└── cmake/                  # CMake utilities
    └── CompilerWarnings.cmake # Compiler warning configuration
```

## Building

### Prerequisites

- CMake 3.28 or higher
- C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)

### Basic Build

```bash
mkdir build && cd build
cmake ..
make
```

### Running the Example

```bash
./src/main
```

### Building with Tests

```bash
mkdir build && cd build
cmake .. -DBUILD_TESTING=ON
make
```

### Running Tests

```bash
make test
# or
ctest
# or run directly
./tests/calculator_test
```

### Building with Benchmarks

```bash
mkdir build && cd build
cmake .. -DBUILD_BENCHMARKS=ON
make
```

### Running Benchmarks

```bash
./benchmarks/calculator_benchmark
```

## CMake Options

- `BUILD_TESTING`: Enable/disable building tests (default: ON when this is the main project)
- `BUILD_BENCHMARKS`: Enable/disable building benchmarks (default: OFF)
- `WARNINGS_AS_ERRORS`: Treat compiler warnings as errors (default: TRUE)

## Dependencies

All dependencies are automatically fetched and built using CMake FetchContent:

- **GoogleTest**: v1.17.0 - Testing framework
- **GoogleMock**: Included with GoogleTest - Mocking framework  
- **Google Benchmark**: v1.9.4 - Performance benchmarking

## Code Guidelines

This project follows strict coding standards:

- **Naming Conventions**: See [docs/naming_conventions.md](docs/naming_conventions.md)
- **Code Formatting**: See [docs/code_guidelines.md](docs/code_guidelines.md)
- **Header Organization**: Specific order and grouping requirements
- **Test Naming**: `MethodName_Scenario_ExpectedBehavior` format
- **Benchmark Naming**: `BM_DescriptiveName` format

### Code Formatting

The project uses clang-format with Microsoft style:

```bash
clang-format -i src/**/*.{cpp,h} include/**/*.h tests/**/*.cpp
```

## Usage as Template

1. Clone or download this repository
2. Replace the example calculator code with your own implementation
3. Update the project name in `CMakeLists.txt`
4. Modify the library name and source files in `src/CMakeLists.txt`
5. Update tests and benchmarks following the naming conventions
6. Follow the coding guidelines in `docs/` directory

## License

MIT License - see LICENSE file for details.
