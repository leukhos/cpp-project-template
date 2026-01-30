# Project Restructuring TODO

This TODO list tracks the ongoing refactoring to align the C++ project with Rust conventions and common C++ practices.

## 3. DocTest Implementation Review

### 3.1 Verify Rust-style test organization
- [ ] Review unit tests in source files (`src/*.cpp`)
  - [ ] Ensure tests verify implementation details
  - [ ] Check test naming convention: `TEST_CASE("Module - scenario")`
- [ ] Review functional tests in `tests/` directory
  - [ ] Ensure tests verify public API only
  - [ ] Check integration test coverage
- [ ] Document distinction between unit and functional tests


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
