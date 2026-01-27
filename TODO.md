# Project Restructuring TODO

This TODO list tracks the ongoing refactoring to align the C++ project with Rust conventions and common C++ practices.

## 1. Project Structure Reorganization

### 1.1 Move directories to root (align with common practice)
- [x] Move `src/include/` to `include/` at project root
  - [x] Update all `#include` paths in source files if needed
  - [x] Update `src/CMakeLists.txt` `BASE_DIRS` from `include` to `${CMAKE_SOURCE_DIR}/include`
  - [x] Update install commands in `src/CMakeLists.txt`
  - [x] Verify FILE_SET still works correctly
- [x] Move `src/cmake/` to `cmake/` at project root
  - [x] Update `install(FILES ./cmake/calculatorConfig.cmake ...)` path in `src/CMakeLists.txt`
  - [x] Update any references to cmake module path
  - [x] Test that package configuration still works for consumers
- [x] Update project structure diagram in [README.md](README.md) to reflect new layout
- [x] Test build and install workflow after restructuring

## 2. CMakePresets Refactoring

### 2.1 Rust-inspired preset organization
Create presets that mirror Rust's cargo profiles:
- [ ] **default** preset (equiv to Rust's dev/debug profile)
  - Debug build
  - Tests enabled
  - No optimizations
  - Full debug symbols
- [ ] **test** preset (equiv to Rust's test profile)
  - Debug or RelWithDebInfo
  - Tests enabled
  - DOCTEST_CONFIG_DISABLE **NOT** defined (enable tests)
  - Coverage instrumentation (optional)
- [ ] **check** preset (equiv to Rust's check/clippy)
  - Fast compilation checks
  - Maximum warnings
  - Treat warnings as errors
  - Static analysis flags
  - No optimization
- [ ] **release** preset (equiv to Rust's release profile)
  - Release configuration
  - Tests disabled
  - Full optimizations
  - LTO enabled
  - DOCTEST_CONFIG_DISABLE defined

### 2.2 Platform-based compiler selection
Refactor to avoid preset duplication:
- [ ] Create platform-specific base presets (hidden)
  - [ ] `linux-base`: Select GCC or Clang based on availability
  - [ ] `windows-base`: Select MSVC
  - [ ] `macos-base`: Select Clang
- [ ] Make profile presets (default, test, check, release) inherit from platform bases
- [ ] Use CMake conditions to automatically select appropriate base
- [ ] Remove explicit compiler-specific presets (gcc, clang, msvc) or make them supplementary

### 2.3 GitHub workflow preset
- [ ] Create `ci` or `github-workflow` preset
  - [ ] Inherits from platform base
  - [ ] Tests enabled
  - [ ] Release optimizations
  - [ ] Suitable for CI/CD pipeline
  - [ ] Matrix-friendly (allow compiler override)

### 2.4 Move DOCTEST_CONFIG_DISABLE to presets
Currently defined in [src/CMakeLists.txt:24](src/CMakeLists.txt#L24)
- [ ] Remove `target_compile_definitions(calculator PRIVATE DOCTEST_CONFIG_DISABLE)` from src/CMakeLists.txt
- [ ] Add DOCTEST_CONFIG_DISABLE to appropriate presets via cacheVariables:
  - [ ] Add to **release** preset
  - [ ] Add to any preset where tests should be compiled out
  - [ ] Ensure **test** and **default** presets do NOT define it
- [ ] Consider using `CALCULATOR_ENABLE_DOCTESTS` CMake option instead for more flexibility
- [ ] Update CMakeLists.txt to conditionally apply DOCTEST_CONFIG_DISABLE based on option

## 3. DocTest Implementation Review

### 3.1 Verify Rust-style test organization
- [ ] Review unit tests in source files (`src/*.cpp`)
  - [ ] Ensure tests verify implementation details
  - [ ] Check test naming convention: `TEST_CASE("Module - scenario")`
- [ ] Review functional tests in `tests/` directory
  - [ ] Ensure tests verify public API only
  - [ ] Check integration test coverage
- [ ] Document distinction between unit and functional tests

### 3.2 Test profile configuration
- [ ] Ensure `test` preset properly enables DocTest
- [ ] Verify `CALCULATOR_BUILD_TESTS` CMake option behavior
- [ ] Consider adding test-specific compiler flags (sanitizers, coverage)
- [ ] Review vcpkg test feature integration

### 3.3 vcpkg test integration
- [ ] Review `VCPKG_MANIFEST_FEATURES` usage for tests
- [ ] Ensure test dependencies (doctest, trompeloeil) are properly gated
- [ ] Verify [vcpkg.json](vcpkg.json) feature configuration

## 4. Complete CMakePresets Review

### 4.1 Preset inheritance structure
- [ ] Design clean inheritance hierarchy
  - Platform bases → Profile types → Specific configurations
- [ ] Minimize duplication
- [ ] Ensure maintainability

### 4.2 Build types and configurations
- [ ] Map CMake build types to Rust profiles
  - Debug → default/dev
  - RelWithDebInfo → test
  - Release → release
  - MinSizeRel → (consider if needed)
- [ ] Define appropriate compiler flags per profile
- [ ] Consider profile-specific optimizations

### 4.3 Testing and validation
- [ ] Test all new presets on Linux
- [ ] Test on macOS (if available)
- [ ] Test on Windows (if available)
- [ ] Verify CI workflow with new presets
- [ ] Update [.github/workflows/](.github/workflows/) to use new presets

## 5. Documentation Review and Update

### 5.1 Naming conventions review
Review [docs/naming_conventions.md](docs/naming_conventions.md):
- [ ] Verify Rust-inspired naming guidelines are accurate
- [ ] Identify conventions that should revert to C++ standards
  - [ ] Member variables (snake_case vs trailing underscore)
  - [ ] Private members naming
  - [ ] Template parameters
  - [ ] Macro naming
- [ ] Update examples to reflect current project state
- [ ] Add rationale for naming choices

### 5.2 Code guidelines review
Review [docs/code_guidelines.md](docs/code_guidelines.md):
- [ ] Verify alignment with Rust conventions where beneficial
- [ ] Identify C++-specific guidelines that differ from Rust
  - [ ] Header inclusion order
  - [ ] Forward declarations
  - [ ] RAII patterns
  - [ ] Template usage
- [ ] Update formatting standards (clang-format)
- [ ] Document CMake conventions

### 5.3 README update
Update [README.md](README.md):
- [ ] Update project structure diagram (after directory moves)
- [ ] Document new CMake presets and their Rust equivalents
- [ ] Update "Using CMake Presets" section
- [ ] Add preset usage examples for each profile (default, test, check, release)
- [ ] Document GitHub workflow preset
- [ ] Update build instructions
- [ ] Clarify DOCTEST_CONFIG_DISABLE behavior

### 5.4 CMake documentation
- [ ] Document CMake options and their defaults
- [ ] Explain preset selection logic
- [ ] Add troubleshooting section
- [ ] Document vcpkg integration details

## 6. Testing and Validation

### 6.1 Build system testing
- [ ] Clean build with each preset
- [ ] Verify library builds correctly
- [ ] Verify tests build and run
- [ ] Verify benchmarks build and run
- [ ] Test install workflow
- [ ] Test package consumption (as a consumer project)

### 6.2 CI/CD validation
- [ ] Update GitHub Actions workflow
- [ ] Test across all supported platforms
- [ ] Verify caching still works
- [ ] Validate test reporting

### 6.3 Documentation validation
- [ ] Follow README instructions from scratch
- [ ] Verify all links work
- [ ] Check code examples compile
- [ ] Proofread for consistency

---

## Notes

- Current branch: `rust-mimic`
- Main branch: `main`
- Project follows Rust-inspired conventions for C++
- Uses vcpkg for dependencies (optional)
- Uses DocTest for testing, Google Benchmark for performance

## Reference: Rust Cargo Profiles

For comparison, standard Rust cargo profiles:
- **dev** (default): Unoptimized, debug info, fast compilation
- **release**: Optimized, minimal debug info
- **test**: Like dev, but for test execution
- **bench**: Like release, but for benchmarks

Our C++ equivalents should provide similar developer experience.
