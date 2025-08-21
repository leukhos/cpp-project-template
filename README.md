# C++ Project Template

A modern C++ project template with CMake build system, vcpkg dependency management, GoogleTest/GoogleMock testing framework, and Google Benchmark performance testing.


## Features

- **CMake Build System**: Modern CMake (3.25+) with FILE_SET support and target-based configuration
- **Optional vcpkg Integration**: CMake presets provide optional vcpkg dependency management with manifest mode - the project is fully independent of vcpkg
- **Testing**: GoogleTest and GoogleMock integration with automatic test discovery
- **Benchmarking**: Google Benchmark for performance testing
- **Modern C++**: C++20 standard with comprehensive compiler warnings
- **Multi-Compiler Support**: CMake presets for GCC, Clang, and MSVC
- **Continuous Integration**: GitHub Actions CI testing across Ubuntu, macOS, and Windows with intelligent caching
- **Code Standards**: Comprehensive coding guidelines and naming conventions
- **Development Container**: Ready-to-use devcontainer configuration based on Microsoft's official containers

## Project Structure

```
cpp-project-template/
├── CMakeLists.txt              # Main CMake configuration
├── CMakePresets.json           # CMake presets for different compilers
├── vcpkg.json                  # vcpkg dependencies manifest
├── vcpkg-configuration.json    # vcpkg configuration
├── src/                        # Source files and headers
│   ├── CMakeLists.txt          # Library target configuration
│   ├── calculator.cpp          # Example implementation
│   ├── include/calculator/     # Public headers (FILE_SET)
│   │   └── calculator.h        # Example header
│   └── cmake/                  # CMake package configuration
│       └── calculatorConfig.cmake
├── tests/                      # Unit tests
│   ├── CMakeLists.txt          # Test executable configuration
│   ├── main.cpp               # Test runner main
│   └── calculator.test.cpp    # Example GoogleTest/GoogleMock tests
├── benchmarks/                 # Performance benchmarks
│   ├── CMakeLists.txt          # Benchmark executable configuration
│   └── calculator.benchmark.cpp # Example Google Benchmark tests
└── docs/                       # Documentation
    ├── code_guidelines.md      # Coding standards and formatting rules
    └── naming_conventions.md   # Naming convention guidelines
```

## CMake Options

- `CALCULATOR_BUILD_TESTS`: Enable/disable building tests (default: OFF)
- `CALCULATOR_BUILD_BENCHMARKS`: Enable/disable building benchmarks (default: OFF)

## Dependencies

The project has minimal runtime dependencies:

- **GoogleTest/GoogleMock**: Testing and mocking framework (enabled with `CALCULATOR_BUILD_TESTS=ON`)
- **Google Benchmark**: Performance benchmarking (enabled with `CALCULATOR_BUILD_BENCHMARKS=ON`)

Dependencies are loaded via CMake's `find_package()` function. The project includes optional vcpkg integration through CMake presets, but this is not required - you can use any dependency management approach you prefer.

## Code Guidelines

This project follows strict coding standards documented in the `docs/` directory:

- **Naming Conventions**: See [docs/naming_conventions.md](docs/naming_conventions.md) for complete naming rules
- **Code Formatting**: See [docs/code_guidelines.md](docs/code_guidelines.md) for formatting and structure guidelines
- **Header Organization**: Critical header inclusion order with mandatory grouping and comments
- **Test Standards**: AAA pattern with `EXPECT_THAT` matchers, `MethodName_Scenario_ExpectedBehavior` naming
- **Benchmark Standards**: `BM_Component_Operation_Scenario_Parameters` naming convention

### Key Standards Summary

- **Classes**: `PascalCase` (Calculator, DataProcessor)
- **Variables**: `snake_case` (counter, file_name)
- **Members**: `m_snake_case` (m_result, m_is_valid) 
- **Functions**: `snake_case` (process_data, get_name)
- **Files**: `snake_case.{h,cpp}` (calculator.h, data_processor.cpp)

### Code Formatting

The project uses clang-format with LLVM style (2-space indentation, 80 character line length):

```bash
clang-format -i src/**/*.{cpp,h} tests/**/*.{cpp,h} benchmarks/**/*.cpp
```

## Using CMake Presets

The project includes CMake presets for different compilers with optional vcpkg integration. All presets share common settings and enable tests by default:

**Common Settings (applied to all presets):**
- Debug configuration (`CMAKE_BUILD_TYPE=Debug`)
- Unit tests enabled (`CALCULATOR_BUILD_TESTS=ON`)
- vcpkg toolchain integration (when `VCPKG_ROOT` is set)
- Output directory: `build/`

**Available Presets:**

- **gcc**: GCC compiler with comprehensive warnings (`-Wall -Wextra -Wpedantic`)
- **clang**: Clang compiler with comprehensive warnings (`-Wall -Wextra -Wpedantic`)  
- **msvc**: MSVC compiler with high warning level (`/W4 /permissive- /EHsc`) - Windows only

```bash
# Configure with any preset
cmake --preset gcc
cmake --preset clang
cmake --preset msvc  # Windows only

# Build the configured project
cmake --build build
```

See `CMakePresets.json` for complete preset configuration details.

## License

MIT License - see LICENSE file for details.
