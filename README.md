# C++ Project Template

A modern C++ project template with CMake build system, vcpkg dependency management, GoogleTest/GoogleMock testing framework, and Google Benchmark performance testing.

## Modification to apply to the README
- vcpkg is just an option provided to handled dependencies. The CMake project does not depends on vcpkg to manage the dependencies. This is only an option provided via CMake presets. The dependencies are loaded via CMake using FindPackage function, but no dependencies to vcpkg are included in the CMakeLists files. This is important to distinguish this. The project is not dependent on vcpkg, once again, I just provide a solution to handle the dependencies, but everyone can use the one he prefer. Same remarks for using the vcpkg features and manifest mode. The preset are using this, but these are only preset, and so no one is obliged to use it. Maybe a section can be required here on how to use the preset (take example on the ci.yml github action commands), specifying that this is not an obligation
- In Features, rework the vcpkg entry, to explicit the fact that this is independent from the CMake project, just in preset. Mentioned the manifest mode
- In Feature, mentioned that the devcontainer is based on microsoft one (nothing extraodinary here)
- Rework the Dependencies section to remove the mention of vcpkg to focus on the real dependencies
- Remove any CLAUDE.md reference
- Remove the "Usage as a template" section, as it seems not relevant. 

## Features

- **CMake Build System**: Modern CMake (3.25+) with FILE_SET support and target-based configuration
- **vcpkg Integration**: Automatic dependency management with CMake presets
- **Testing**: GoogleTest and GoogleMock integration with automatic test discovery
- **Benchmarking**: Google Benchmark for performance testing
- **Modern C++**: C++20 standard with comprehensive compiler warnings
- **Multi-Compiler Support**: CMake presets for GCC, Clang, and MSVC
- **Continuous Integration**: GitHub Actions CI testing across Ubuntu, macOS, and Windows with intelligent caching
- **Code Standards**: Comprehensive coding guidelines and naming conventions
- **Development Container**: Ready-to-use devcontainer configuration

## Project Structure

```
cpp-project-template/
├── CMakeLists.txt              # Main CMake configuration
├── CMakePresets.json           # CMake presets for different compilers
├── vcpkg.json                  # vcpkg dependencies manifest
├── vcpkg-configuration.json    # vcpkg configuration
├── CLAUDE.md                   # Claude Code guidance document
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

Dependencies are managed through vcpkg with feature-based configuration:

- **GoogleTest/GoogleMock**: Testing and mocking framework (vcpkg feature: `tests`)
- **Google Benchmark**: Performance benchmarking (vcpkg feature: `benchmarks`)

See `vcpkg.json` for the complete dependency configuration.

## Code Guidelines

This project follows strict coding standards:

- **Naming Conventions**: See [docs/naming_conventions.md](docs/naming_conventions.md)
- **Code Formatting**: See [docs/code_guidelines.md](docs/code_guidelines.md)
- **Header Organization**: Specific order and grouping requirements
- **Test Naming**: `MethodName_Scenario_ExpectedBehavior` format
- **Benchmark Naming**: `BM_DescriptiveName` format

### Code Formatting

The project uses clang-format with LLVM style:

```bash
clang-format -i src/**/*.{cpp,h} tests/**/*.cpp benchmarks/**/*.cpp
```

## Usage as Template

1. Clone or download this repository
2. Replace the example calculator code with your own implementation
3. Update the project name in `CMakeLists.txt`
4. Modify the library name and source files in `src/CMakeLists.txt`
5. Update `vcpkg.json` with your specific dependencies
6. Update tests and benchmarks following the naming conventions
7. Follow the coding guidelines in `docs/` directory
8. See `CLAUDE.md` for detailed development guidance

## License

MIT License - see LICENSE file for details.
