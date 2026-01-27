# C++ Project Template (Rust-Inspired)

A modern C++ project template following Rust language conventions, with CMake build system, vcpkg dependency management, DocTest testing framework, and Google Benchmark performance testing.


## Features

- **Rust-Inspired Conventions**: Follows Rust naming and project structure patterns in C++
- **CMake Build System**: Modern CMake (3.25+) with FILE_SET support and target-based configuration
- **Optional vcpkg Integration**: CMake presets provide optional vcpkg dependency management with manifest mode - the project is fully independent of vcpkg
- **Testing**: DocTest framework with Rust-style test organization
- **Benchmarking**: Google Benchmark in `benches/` directory (Rust convention)
- **Modern C++**: C++20 standard with comprehensive compiler warnings
- **Multi-Compiler Support**: CMake presets for GCC, Clang, and MSVC
- **Continuous Integration**: GitHub Actions CI testing across Ubuntu, macOS, and Windows with intelligent caching
- **Code Standards**: Rust-inspired coding guidelines and naming conventions
- **Development Container**: Ready-to-use devcontainer configuration based on Microsoft's official containers

## Project Structure

```
cpp-project-template/
├── CMakeLists.txt              # Main CMake configuration
├── CMakePresets.json           # CMake presets for different compilers
├── vcpkg.json                  # vcpkg dependencies manifest
├── vcpkg-configuration.json    # vcpkg configuration
├── include/calculator/         # Public headers (FILE_SET)
│   └── calculator.h            # Example header
├── cmake/                      # CMake package configuration
│   └── calculatorConfig.cmake
├── src/                        # Source files
│   ├── CMakeLists.txt          # Library target configuration
│   └── calculator.cpp          # Implementation + unit tests (Rust-style)
├── tests/                      # Functional/Integration tests (Rust-style)
│   ├── CMakeLists.txt          # Test executable configuration
│   └── calculator.test.cpp    # Functional tests for public API
├── benches/                    # Performance benchmarks (Rust convention)
│   ├── CMakeLists.txt          # Benchmark executable configuration
│   └── calculator.benchmark.cpp # snake_case benchmark functions
└── docs/                       # Documentation
    ├── code_guidelines.md      # Rust-inspired coding standards
    └── naming_conventions.md   # Rust-inspired naming conventions
```

## CMake Options

- `CALCULATOR_BUILD_TESTS`: Enable/disable building tests (default: OFF)
- `CALCULATOR_BUILD_BENCHMARKS`: Enable/disable building benchmarks (default: OFF)

## Dependencies

The project has minimal runtime dependencies:

- **DocTest**: Lightweight, header-only testing framework (enabled with `CALCULATOR_BUILD_TESTS=ON`)
- **Trompeloeil**: Modern C++ mocking framework (enabled with `CALCULATOR_BUILD_TESTS=ON`)
- **Google Benchmark**: Performance benchmarking (enabled with `CALCULATOR_BUILD_BENCHMARKS=ON`)

Dependencies are loaded via CMake's `find_package()` function. The project includes optional vcpkg integration through CMake presets, but this is not required - you can use any dependency management approach you prefer.

## Code Guidelines (Rust-Inspired)

This project follows Rust-inspired coding standards documented in the `docs/` directory:

- **Naming Conventions**: See [docs/naming_conventions.md](docs/naming_conventions.md) for Rust-style naming rules
- **Code Formatting**: See [docs/code_guidelines.md](docs/code_guidelines.md) for formatting and structure guidelines
- **Header Organization**: Critical header inclusion order with mandatory grouping and comments
- **Test Organization**:
  - **Unit tests**: Embedded in source files (`src/*.cpp`) - test implementation details
  - **Functional tests**: In `tests/` directory - test public API and workflows
- **Test Standards**: AAA pattern with DocTest, `TEST_CASE("Module - scenario")` naming
- **Benchmark Standards**: `benchmark_component_operation_scenario` snake_case naming

### Key Standards Summary (Rust-Inspired)

- **Classes/Structs**: `PascalCase` (Calculator, DataProcessor)
- **Variables**: `snake_case` (counter, file_name)
- **Members**: `snake_case` - NO prefixes (result, is_valid)
- **Functions**: `snake_case` (process_data, get_name)
- **Constants**: `SCREAMING_SNAKE_CASE` (MAX_BUFFER_SIZE)
- **Namespaces**: `snake_case` (data_processing, networking)
- **Error Types**: `PascalCaseError` (FileNotFoundError, ParseError)
- **Traits**: `PascalCase` - NO "I" prefix (Drawable, Serializable)
- **Files**: `snake_case.{h,cpp}` (calculator.h, data_processor.cpp)

### Code Formatting

The project uses clang-format with LLVM style (2-space indentation, 80 character line length):

```bash
clang-format -i src/**/*.{cpp,h} tests/**/*.{cpp,h} benches/**/*.cpp
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
