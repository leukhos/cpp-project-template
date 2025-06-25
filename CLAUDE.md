# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is a C++ project template repository that provides a modern C++ project structure with CMake build system, GoogleTest/GoogleMock testing framework, and Google Benchmark performance testing. The template includes example code demonstrating best practices and proper project organization.

## C++ Naming Guidelines

See [docs/naming_conventions.md](docs/naming_conventions.md) for detailed naming conventions.

## Current Status
The project template is fully implemented with:
- CMake build system with FetchContent dependency management
- GoogleTest and GoogleMock testing framework
- Google Benchmark performance testing
- Example Calculator class demonstrating the structure

## Expected Project Structure
When fully implemented, this template should likely include:
- `src/` - Source code directory
- `include/` - Header files
- `tests/` - Unit tests
- `benchmarks/` - Performance benchmarks
- `CMakeLists.txt` - Main CMake configuration
- `cmake/` - CMake modules and utilities

## Build Commands
*Note: Build system not yet implemented*
Once CMake is set up, typical commands would be:
```bash
mkdir build && cd build
cmake ..
make
```

## Testing
*Note: Testing framework not yet implemented*
Once testing is configured, typical command would be:
```bash
make test
# or
ctest
```

## Development Notes
- Uses MIT License
- Standard C++ .gitignore is configured for compiled objects, libraries, and executables
- Project is tracked in Git with initial commit completed