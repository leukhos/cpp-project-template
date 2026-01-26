# C++ Code Guidelines (Rust-Inspired)

This document provides comprehensive coding standards for this C++ project, following Rust-inspired conventions.

## Quick Reference

### Headers (Order & Grouping)
1. Precompiled headers (`#include "pch.h"`)
2. First-party headers (`#include "calculator.h"`)
3. Third-party headers (`#include <doctest/doctest.h>`)
4. Standard library (`#include <iostream>`)

### Test Naming (DocTest)
- Test cases: `TEST_CASE("Module - Scenario")`
- Subcases: `SUBCASE("specific scenario")`
- Example: `TEST_CASE("Calculator - addition with positive numbers")`

### Benchmark Naming
`snake_case` functions in `benches/` directory
- Example: `benchmark_vector_push_back`, `benchmark_sort_random_1k`

### Formatting
- LLVM style (clang-format)
- 2-space indentation
- Run: `clang-format -i src/**/*.{cpp,h} tests/**/*.{cpp,h} benches/**/*.cpp`

## Code Formatting (RULES)

The project uses `clang-format` with LLVM style as the base configuration. The specific formatting rules are defined in `.clang-format`:

- **Base Style**: LLVM
- **Indentation**: 2 spaces (LLVM default)
- **Brace Style**: Attach (LLVM default)
- **Line Length**: 80 characters (LLVM default)

**IMPORTANT**: Always run clang-format before committing:
```bash
clang-format -i src/**/*.{cpp,h} tests/**/*.{cpp,h} benchmarks/**/*.cpp
```

## Header Inclusion Rules (CRITICAL)

### Inclusion Policy
- **No implicit inclusion**: All dependencies must be explicitly included
- **No transitive dependencies**: Do not rely on headers included by other headers  
- **Forward declarations**: Use forward declarations whenever possible to reduce compilation dependencies
- **Always add header comments**: Group headers with comments as shown in examples

### Header Sorting Order (MANDATORY)

Headers MUST be grouped and sorted in this exact order with comments:

1. **Precompiled Headers** (if existing)
   ```cpp
   // Precompiled headers
   #include "pch.h"
   ```

2. **First-party Headers** (project headers)
   ```cpp
   // First-party headers
   #include "calculator.h"
   #include "data_processor.h"
   ```

3. **Third-party Headers** (external libraries)
   ```cpp
   // Third-party headers
   #include <doctest/doctest.h>
   #include <benchmark/benchmark.h>
   ```

4. **Standard Library Headers**
   ```cpp
   // Standard library headers
   #include <algorithm>
   #include <memory>
   #include <string>
   #include <vector>
   ```

### Sorting Within Groups (RULES)
- Sort alphabetically within each group
- **ALWAYS use blank lines to separate groups**
- **ALWAYS add group comment headers** (see examples)
- Third-party headers may be sub-grouped by library/framework if it improves readability

### Example Header Organization
```cpp
// Precompiled header (if used)
#include "pch.h"

// First-party headers
#include "calculator.h"
#include "math_utils.h"

// Third-party headers
#include <doctest/doctest.h>
#include <benchmark/benchmark.h>

// Standard library headers
#include <iostream>
#include <memory>
#include <vector>
```

### Rationale (EXPLANATION)

This header organization ensures:
- **Dependency clarity**: All dependencies are explicit and visible
- **Build reliability**: No hidden dependencies through transitive inclusion
- **Maintainability**: Easy to identify what each file depends on
- **Compilation speed**: Precompiled headers first, followed by logical dependency order

## Testing Guidelines (CRITICAL - DocTest Framework)

### Test Organization (MANDATORY - Rust-Style)

Following Rust conventions, this project uses two types of tests:

#### 1. Unit Tests (In Source Files)
**Location**: Embedded in source files (e.g., `src/calculator.cpp`)

**Purpose**: Test internal implementation details and individual functions in isolation

**Characteristics**:
- Live alongside the code they test (Rust's `#[cfg(test)]` pattern)
- Have access to private/internal implementation details
- Test individual methods and edge cases
- Always include `<doctest/doctest.h>` at the top of the file
- Tests are disabled in production builds via `DOCTEST_CONFIG_DISABLE`
- Tests are enabled in test builds (when `DOCTEST_CONFIG_DISABLE` is not defined)

**Example**:
```cpp
// src/calculator.cpp
#include "calculator/calculator.h"

// Always include DocTest header
#include <doctest/doctest.h>

#include <stdexcept>

int Calculator::add(int first_value, int second_value) {
  return first_value + second_value;
}

// Unit tests at the bottom of the file
// These compile to nothing when DOCTEST_CONFIG_DISABLE is defined (production builds)
TEST_CASE("Calculator - addition operations") {
  Calculator calculator;

  SUBCASE("addition with positive numbers") {
    CHECK(calculator.add(2, 3) == 5);
  }

  SUBCASE("addition with negative numbers") {
    CHECK(calculator.add(-2, -3) == -5);
  }
}
```

**How it works**:
- **Production/Library build**: CMake defines `DOCTEST_CONFIG_DISABLE`, tests compile to nothing (zero overhead)
- **Test build**: CMake does NOT define `DOCTEST_CONFIG_DISABLE`, tests are compiled and run
- This mirrors Rust's `#[cfg(test)]` attribute which strips tests from release builds

**CMake Configuration**:
```cmake
# src/CMakeLists.txt (Library build)
find_package(doctest REQUIRED)
target_link_libraries(calculator PRIVATE doctest::doctest)
# Disable tests in production
target_compile_definitions(calculator PRIVATE DOCTEST_CONFIG_DISABLE)

# tests/CMakeLists.txt (Test build)
find_package(doctest REQUIRED)
# Compile source files again, but WITHOUT DOCTEST_CONFIG_DISABLE
target_sources(calculator_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/calculator.cpp)
target_link_libraries(calculator_tests PRIVATE doctest::doctest)
# Tests are now enabled!
```

#### 2. Functional/Integration Tests (In tests/ Directory)
**Location**: `tests/` directory (e.g., `tests/calculator.test.cpp`)

**Purpose**: Test the public API and behavior from a user's perspective

**Characteristics**:
- Test the library as an external user would use it
- Only access public APIs (through headers)
- Test workflows, integration, and real-world scenarios
- May use mocking for dependencies
- One file typically has `DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`

**Example**:
```cpp
// tests/calculator.test.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "calculator/calculator.h"

TEST_CASE("Calculator - functional test for workflow") {
  Calculator calculator;

  SUBCASE("performing multiple operations in sequence") {
    int result = calculator.add(100, 50);
    result = calculator.subtract(result, 30);
    result = calculator.multiply(result, 2);

    CHECK(result == 240); // (100 + 50 - 30) * 2
  }
}
```

#### When to Use Which Test Type

**Use Unit Tests when**:
- Testing individual methods in isolation
- Testing internal logic and implementation details
- Verifying edge cases and boundary conditions
- You need to test private methods or internal state

**Use Functional Tests when**:
- Testing the public API behavior
- Testing workflows and real-world scenarios
- Testing integration between components
- Testing error handling in realistic contexts
- Using mocks to simulate dependencies

### Test Naming Convention (MANDATORY FORMAT - Rust/DocTest Style)
Test names use descriptive strings: `TEST_CASE("Module - Scenario - Expected Behavior")`

**Structure:**
- **Module/Component**: What is being tested
- **Scenario**: Specific conditions or input
- **Expected behavior** (optional): Can be implicit in scenario description

**Examples:**
```cpp
TEST_CASE("Calculator - addition with positive numbers") {
  // Test implementation
}

TEST_CASE("Calculator - division by zero throws exception") {
  // Test implementation
}

TEST_CASE("Calculator - multiplication with zero returns zero") {
  // Test implementation
}
```

### Test Structure (MANDATORY AAA Pattern)
All tests MUST use the AAA pattern with explicit comments:

1. **Arrange**: Set up test data and preconditions
2. **Act**: Execute the method or behavior being tested
3. **Assert**: Verify the expected outcome

**ALWAYS include AAA comments in tests:**

```cpp
TEST_CASE("Calculator - addition with positive numbers") {
  // Arrange
  Calculator calculator;
  int first_value = 5;
  int second_value = 3;
  int expected = 8;

  // Act
  int result = calculator.add(first_value, second_value);

  // Assert
  CHECK(result == expected);
}
```

### Test Organization (GUIDELINES - DocTest)
- **Use TEST_CASE**: Primary test macro for DocTest
- **Use SUBCASE**: For grouping related scenarios within a test
- **Descriptive names**: Use clear, readable test case descriptions
- **Group with subcases**: Related tests can share setup using SUBCASE

**SUBCASE Example:**
```cpp
TEST_CASE("Calculator - arithmetic operations") {
  Calculator calculator;  // Shared setup

  SUBCASE("addition with positive numbers") {
    // Arrange
    int first_value = 5;
    int second_value = 3;

    // Act
    int result = calculator.add(first_value, second_value);

    // Assert
    CHECK(result == 8);
  }

  SUBCASE("subtraction with positive numbers") {
    // Arrange
    int first_value = 5;
    int second_value = 3;

    // Act
    int result = calculator.subtract(first_value, second_value);

    // Assert
    CHECK(result == 2);
  }
}
```

### Exception Testing (GUIDELINES - DocTest)
When testing exceptions, use `CHECK_THROWS_AS` or `CHECK_THROWS_WITH`:

```cpp
TEST_CASE("Calculator - division by zero throws exception") {
  // Arrange
  Calculator calculator;

  // Act & Assert
  CHECK_THROWS_AS(calculator.divide(10, 0), std::invalid_argument);
}

// Or with message verification:
TEST_CASE("Calculator - division by zero has correct message") {
  Calculator calculator;
  CHECK_THROWS_WITH(calculator.divide(10, 0), "Division by zero");
}
```

### Assertion Guidelines (MANDATORY - DocTest)

**DocTest Assertions:**

```cpp
// Basic assertions
CHECK(result == expected);           // Non-fatal assertion
REQUIRE(ptr != nullptr);             // Fatal assertion (stops test on failure)

// Floating point comparisons
CHECK(result == doctest::Approx(expected_double).epsilon(0.01));

// Exception testing
CHECK_THROWS(risky_operation());                        // Any exception
CHECK_THROWS_AS(divide_by_zero(), std::invalid_argument);  // Specific type
CHECK_THROWS_WITH(parse_error(), "invalid format");     // With message
CHECK_NOTHROW(safe_operation());                        // No exception

// Logical assertions
CHECK_FALSE(is_empty);
CHECK_UNARY(value > 0);
CHECK_UNARY_FALSE(is_negative);
```

**Required includes:**
```cpp
// Third-party headers
#include <doctest/doctest.h>
```

**Benefits of DocTest:**
- **Lightweight**: Header-only, minimal dependencies
- **Fast compilation**: Significantly faster than GoogleTest
- **Rust-like**: Similar to Rust's built-in test framework
- **Clear output**: Excellent error messages and diagnostics
- **Flexible**: Can be used for both unit and integration tests

### Mocking Guidelines (GUIDELINES - Trompeloeil)

For mocking, this project uses **Trompeloeil**, a modern C++ mocking framework that integrates seamlessly with DocTest.

**Creating Mock Objects:**

```cpp
// Define an interface
class CalculatorInterface {
public:
  virtual ~CalculatorInterface() = default;
  virtual int add(int first_value, int second_value) = 0;
  virtual int subtract(int first_value, int second_value) = 0;
};

// Create mock implementation
class MockCalculator : public CalculatorInterface {
public:
  MAKE_MOCK2(add, int(int, int), override);
  MAKE_MOCK2(subtract, int(int, int), override);
};
```

**Using Mocks in Tests:**

```cpp
TEST_CASE("MockCalculator - mocking with Trompeloeil") {
  SUBCASE("addition with mock returns expected value") {
    // Arrange
    MockCalculator mock_calculator;
    int first_value = 2;
    int second_value = 3;
    int expected_result = 5;

    REQUIRE_CALL(mock_calculator, add(first_value, second_value))
        .RETURN(expected_result);

    // Act
    int result = mock_calculator.add(first_value, second_value);

    // Assert
    CHECK(result == expected_result);
  }
}
```

**Trompeloeil Key Features:**

- `MAKE_MOCK0` through `MAKE_MOCK15`: Define mock methods (number = parameter count)
- `REQUIRE_CALL`: Expectation that MUST be satisfied
- `ALLOW_CALL`: Optional expectation
- `FORBID_CALL`: Ensure method is NOT called
- `.RETURN(value)`: Specify return value
- `.THROW(exception)`: Specify exception to throw
- `.TIMES(n)`: Specify how many times method should be called
- `.WITH(matcher)`: Argument matchers for flexible matching

**Advanced Mocking Examples:**

```cpp
TEST_CASE("Advanced mocking examples") {
  MockCalculator mock;

  SUBCASE("verify method called multiple times") {
    REQUIRE_CALL(mock, add(trompeloeil::_, trompeloeil::_))
        .TIMES(3)
        .RETURN(0);

    mock.add(1, 2);
    mock.add(3, 4);
    mock.add(5, 6);
  }

  SUBCASE("verify specific arguments") {
    REQUIRE_CALL(mock, add(2, 3))
        .RETURN(5);

    CHECK(mock.add(2, 3) == 5);
  }

  SUBCASE("throw exception from mock") {
    REQUIRE_CALL(mock, divide(trompeloeil::_, 0))
        .THROW(std::invalid_argument("Division by zero"));

    CHECK_THROWS_AS(mock.divide(10, 0), std::invalid_argument);
  }
}
```

**Required includes:**
```cpp
// Third-party headers
#include <trompeloeil.hpp>
#include <doctest/doctest.h>
```

**Benefits of Trompeloeil:**
- **Modern C++**: Uses C++11/14 features, header-only
- **Clear syntax**: Readable expectation definitions
- **Framework agnostic**: Works with DocTest, GoogleTest, Catch2, etc.
- **Excellent diagnostics**: Clear error messages on expectation failures
- **Type safe**: Compile-time type checking of mock expectations

### Testing Best Practices (GUIDELINES)
- **One assertion per test**: Each test should verify a single behavior or outcome
- **Descriptive test names**: Test names should be readable and explain the test purpose without looking at the implementation
- **Independent tests**: Tests should not depend on each other and should be able to run in any order
- **Fast execution**: Keep tests fast by avoiding unnecessary setup, file I/O, or network calls
- **Deterministic results**: Tests should produce the same result every time they run
- **Test edge cases**: Include boundary conditions, null values, empty collections, and error scenarios
- **Avoid magic numbers**: Use named constants or variables to make test data meaningful
- **Mock external dependencies**: Use mocks to isolate the unit under test from external systems
- **Clean up resources**: Ensure tests properly clean up any resources they create
- **Use fixtures wisely**: Share setup code through test fixtures, but avoid over-coupling tests

### Test Data Management (EXAMPLES - DocTest)

```cpp
// Good: Use meaningful constants
TEST_CASE("Calculator - addition with large numbers") {
  // Arrange
  Calculator calculator;
  const int first_large_number = 999999;
  const int second_large_number = 888888;
  const int expected_sum = 1888887;

  // Act
  int result = calculator.add(first_large_number, second_large_number);

  // Assert
  CHECK(result == expected_sum);
}

// Avoid: Magic numbers without context
TEST_CASE("Calculator - addition") {
  Calculator calculator;
  CHECK(calculator.add(42, 17) == 59); // What's special about 42 and 17?
}
```

## Benchmarking Guidelines (GUIDELINES - Rust-Inspired)

### Benchmark Location (MANDATORY)
- All benchmarks MUST be in the `benches/` directory (Rust convention)
- Use `snake_case` for benchmark file names: `calculator.benchmark.cpp`

### Benchmark Naming Convention (MANDATORY FORMAT - Rust Style)

Benchmark functions use `snake_case` following Rust conventions:

**Naming pattern:** `benchmark_[component]_[operation]_[scenario]_[parameters]`

**Components:**
1. **benchmark_** - Prefix for clarity (optional but recommended)
2. **component** - The module or type being benchmarked
3. **operation** - The specific method or functionality
4. **scenario** - The test conditions (optional)
5. **parameters** - Size or configuration details (optional)

### Naming Patterns and Examples (EXAMPLES - Rust Style)

#### Basic Structure
```cpp
// Pattern: benchmark_component_operation
static void benchmark_vector_push_back(benchmark::State& state) { /* ... */ }
static void benchmark_map_insert(benchmark::State& state) { /* ... */ }
static void benchmark_string_find(benchmark::State& state) { /* ... */ }
```

#### With Scenarios
```cpp
// Pattern: benchmark_component_operation_scenario
static void benchmark_vector_push_back_empty(benchmark::State& state) { /* ... */ }
static void benchmark_vector_push_back_preallocated(benchmark::State& state) { /* ... */ }
static void benchmark_map_insert_sequential(benchmark::State& state) { /* ... */ }
static void benchmark_map_insert_random(benchmark::State& state) { /* ... */ }
```

#### With Parameters
```cpp
// Pattern: benchmark_component_operation_scenario_parameters
static void benchmark_sort_quicksort_random_small(benchmark::State& state) { /* ... */ }
static void benchmark_sort_quicksort_random_large(benchmark::State& state) { /* ... */ }
static void benchmark_hash_lookup_uniform_1k(benchmark::State& state) { /* ... */ }
static void benchmark_hash_lookup_skewed_10k(benchmark::State& state) { /* ... */ }
```

### Specific Naming Conventions (EXAMPLES - Rust Style)

#### Data Structure Benchmarks
```cpp
static void benchmark_vector_access_sequential(benchmark::State& state);
static void benchmark_vector_access_random(benchmark::State& state);
static void benchmark_list_traverse_forward(benchmark::State& state);
static void benchmark_hashmap_lookup_hit(benchmark::State& state);
static void benchmark_hashmap_lookup_miss(benchmark::State& state);
```

#### Algorithm Benchmarks
```cpp
static void benchmark_sort_mergesort_sorted(benchmark::State& state);
static void benchmark_sort_mergesort_reverse(benchmark::State& state);
static void benchmark_search_binary_search_found(benchmark::State& state);
static void benchmark_search_linear_search_not_found(benchmark::State& state);
```

#### I/O and System Benchmarks
```cpp
static void benchmark_file_read_sequential_4kb(benchmark::State& state);
static void benchmark_file_write_random_1mb(benchmark::State& state);
static void benchmark_network_tcp_send_small(benchmark::State& state);
static void benchmark_memory_allocate_aligned(benchmark::State& state);
```

### Parameter-Driven Benchmarks (GUIDELINES - Rust Style)

For benchmarks that test multiple sizes or configurations, use Google Benchmark's parameter features:

```cpp
// Use descriptive base names with parameters (snake_case)
static void benchmark_vector_push_back(benchmark::State& state) {
  auto size = state.range(0);
  // Implementation...
}
BENCHMARK(benchmark_vector_push_back)->Range(8, 8<<10);

// Or with custom arguments
static void benchmark_matrix_multiply(benchmark::State& state) {
  auto rows = state.range(0);
  auto cols = state.range(1);
  // Implementation...
}
BENCHMARK(benchmark_matrix_multiply)->Args({64, 64})->Args({128, 128})->Args({256, 256});
```

### Benchmarking Best Practices (GUIDELINES)

#### DO:
- **Use descriptive scenario names**: `Empty`, `Preallocated`, `Sequential`, `Random`, `Sorted`, `Reverse`
- **Include data characteristics**: `Small`, `Large`, `Dense`, `Sparse`, `Uniform`, `Skewed`
- **Specify success/failure cases**: `Hit`, `Miss`, `Found`, `NotFound`, `Success`, `Failure`
- **Use consistent terminology**: Stick to the same terms across related benchmarks
- **Group related benchmarks**: Use common prefixes for benchmark families

#### DON'T:
- Use abbreviations unless they're widely understood (`TCP`, `HTTP`, `JSON` are fine)
- Make names too long (>60 characters becomes unwieldy)
- Include implementation details that might change
- Use spaces or special characters (stick to alphanumeric and underscores)

### Size Indicators (GUIDELINES - Rust Style)
```cpp
// Use standard size indicators (lowercase in snake_case)
static void benchmark_container_operation_1k(benchmark::State& state);   // ~1,000 elements
static void benchmark_container_operation_1m(benchmark::State& state);   // ~1,000,000 elements
static void benchmark_buffer_copy_4kb(benchmark::State& state);          // 4 kilobytes
static void benchmark_cache_lookup_l1(benchmark::State& state);          // L1 cache size
```

### Example Benchmark Suite (EXAMPLES - Rust Style)

```cpp
// String processing benchmarks
static void benchmark_string_find_short_found(benchmark::State& state);
static void benchmark_string_find_short_not_found(benchmark::State& state);
static void benchmark_string_find_long_found(benchmark::State& state);
static void benchmark_string_replace_single(benchmark::State& state);
static void benchmark_string_replace_multiple(benchmark::State& state);

// Container benchmarks
static void benchmark_vector_insert_front(benchmark::State& state);
static void benchmark_vector_insert_middle(benchmark::State& state);
static void benchmark_vector_insert_back(benchmark::State& state);
static void benchmark_deque_insert_front(benchmark::State& state);
static void benchmark_deque_insert_back(benchmark::State& state);

// Algorithm benchmarks
static void benchmark_sort_introsort_random_1k(benchmark::State& state);
static void benchmark_sort_introsort_sorted_1k(benchmark::State& state);
static void benchmark_sort_introsort_reverse_1k(benchmark::State& state);
```

### Registration Patterns (GUIDELINES - Rust Style)

When registering benchmarks, maintain consistency with snake_case:

```cpp
// Simple registration
BENCHMARK(benchmark_vector_push_back);

// With parameters
BENCHMARK(benchmark_sort_quicksort)->Range(1<<10, 1<<18);

// With custom arguments
BENCHMARK(benchmark_hash_insert)->Args({1000, 75})->Args({10000, 90});

// With time units
BENCHMARK(benchmark_algorithm_process)->Unit(benchmark::kMicrosecond);
```

Following these Rust-inspired guidelines will make your benchmarks more maintainable, easier to understand, and consistent with modern C++ practices.
