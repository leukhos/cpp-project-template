# C++ Project Template

A modern C++ project template with CMake build system, GoogleTest/GoogleMock testing framework, and Google Benchmark performance testing.

## Todo
2. Add some documentation about code guidelines, like header sorting rules
4. Add testing and benchmarking structure guidelines
5. Review google library version (should we use latest?)
3. Update README.md and CLAUDE.md

## Features

- **CMake Build System**: Modern CMake (3.14+) with proper target-based configuration
- **Testing**: GoogleTest and GoogleMock integration with automatic test discovery
- **Benchmarking**: Google Benchmark for performance testing
- **Dependencies**: Automatic dependency management using CMake FetchContent
- **Modern C++**: C++17 standard with comprehensive compiler warnings

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
│   └── test_calculator.cpp # Example GoogleTest/GoogleMock tests
├── benchmarks/             # Performance benchmarks
│   ├── CMakeLists.txt
│   └── bench_calculator.cpp # Example Google Benchmark tests
└── cmake/                  # CMake utilities
    └── CompilerWarnings.cmake # Compiler warning configuration
```

## Building

### Prerequisites

- CMake 3.14 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

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
./tests/calculator_tests
```

### Building with Benchmarks

```bash
mkdir build && cd build
cmake .. -DBUILD_BENCHMARKS=ON
make
```

### Running Benchmarks

```bash
./benchmarks/calculator_benchmarks
```

## CMake Options

- `BUILD_TESTING`: Enable/disable building tests (default: ON when this is the main project)
- `BUILD_BENCHMARKS`: Enable/disable building benchmarks (default: OFF)
- `WARNINGS_AS_ERRORS`: Treat compiler warnings as errors (default: TRUE)

## Dependencies

All dependencies are automatically fetched and built using CMake FetchContent:

- **GoogleTest**: v1.14.0 - Testing framework
- **GoogleMock**: Included with GoogleTest - Mocking framework  
- **Google Benchmark**: v1.8.3 - Performance benchmarking

## Usage as Template

1. Clone or download this repository
2. Replace the example calculator code with your own implementation
3. Update the project name in `CMakeLists.txt`
4. Modify the library name and source files in `src/CMakeLists.txt`
5. Update tests and benchmarks accordingly

## License

MIT License - see LICENSE file for details.
