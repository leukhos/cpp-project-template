# C++ Code Guidelines

This document provides comprehensive coding standards for Claude Code when working with this C++ project.

## Quick Reference

### Headers (Order & Grouping)
1. Precompiled headers (`#include "pch.h"`)
2. First-party headers (`#include "calculator.h"`)
3. Third-party headers (`#include <gtest/gtest.h>`)
4. Standard library (`#include <iostream>`)

### Test Naming
`MethodName_Scenario_ExpectedBehavior`
- Example: `Add_PositiveNumbers_ReturnsCorrectSum`

### Benchmark Naming
`BM_DescriptiveName`
- Example: `BM_Addition`, `BM_LargeVectorSort`

### Formatting
- LLVM style (clang-format)
- 2-space indentation
- Run: `clang-format -i src/**/*.{cpp,h} include/**/*.h tests/**/*.cpp`

## Code Formatting

The project uses `clang-format` with LLVM style as the base configuration. The specific formatting rules are defined in `.clang-format`:

- **Base Style**: LLVM
- **Indentation**: 2 spaces (LLVM default)
- **Brace Style**: Attach (LLVM default)
- **Line Length**: 80 characters (LLVM default)

**IMPORTANT**: Always run clang-format before committing:
```bash
clang-format -i src/**/*.{cpp,h} include/**/*.h tests/**/*.cpp
```

## Header Inclusion Rules

### Inclusion Policy (CRITICAL)
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
   #include <gtest/gtest.h>
   #include <gmock/gmock.h>
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
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

// Standard library headers
#include <iostream>
#include <memory>
#include <vector>
```

### Rationale

This header organization ensures:
- **Dependency clarity**: All dependencies are explicit and visible
- **Build reliability**: No hidden dependencies through transitive inclusion
- **Maintainability**: Easy to identify what each file depends on
- **Compilation speed**: Precompiled headers first, followed by logical dependency order

## Testing Guidelines

### Test Naming Convention (MANDATORY FORMAT)
Test names MUST follow: `MethodName_Scenario_ExpectedBehavior`

**Three required components:**
- **Method being tested**: Exact method or functionality under test
- **Scenario**: Specific conditions or input that triggers the test case  
- **Expected behavior**: Anticipated outcome or result

**Examples of good names:**
- `Add_PositiveNumbers_ReturnsCorrectSum`
- `Divide_ByZero_ThrowsInvalidArgumentException`
- `Parse_EmptyString_ReturnsEmptyResult`

Examples:
```cpp
TEST_F(CalculatorTest, Add_PositiveNumbers_ReturnsCorrectSum)
TEST_F(CalculatorTest, Divide_ByZero_ThrowsInvalidArgumentException)
TEST_F(CalculatorTest, Multiply_WithZero_ReturnsZero)
```

### Test Structure (MANDATORY AAA Pattern)
All tests MUST use the AAA pattern with explicit comments:

1. **Arrange**: Set up test data and preconditions
2. **Act**: Execute the method or behavior being tested  
3. **Assert**: Verify the expected outcome

**ALWAYS include AAA comments in tests:**

```cpp
TEST_F(CalculatorTest, Add_PositiveNumbers_ReturnsCorrectSum) {
  // Arrange
  Calculator calculator;
  int firstValue = 5;
  int secondValue = 3;
  int expected = 8;

  // Act
  int result = calculator.add(firstValue, secondValue);

  // Assert
  EXPECT_THAT(result, Eq(expected));
}
```

### Test Organization
- Use test fixtures (`TEST_F`) for tests that share setup/teardown
- Group related tests in the same test class
- Use descriptive test class names ending with "Test"
- Place mock classes immediately after the main test class

### Exception Testing
When testing exceptions, be specific about the expected exception type:
```cpp
TEST_F(CalculatorTest, Divide_ByZero_ThrowsInvalidArgumentException) {
  // Arrange
  Calculator calculator;

  // Act & Assert
  EXPECT_THAT([&]() { return calculator.divide(10, 0); }, Throws<std::invalid_argument>());
}
```

### Assertion Guidelines (MANDATORY)

**ALWAYS prefer `EXPECT_THAT` with matchers over legacy assertions:**

```cpp
// Preferred: Use EXPECT_THAT with matchers
EXPECT_THAT(result, Eq(expectedValue));
EXPECT_THAT(result, DoubleEq(expectedDouble));
EXPECT_THAT([&]() { return calculator.divide(10, 0); }, Throws<std::invalid_argument>());

// Avoid: Legacy assertion macros
EXPECT_EQ(result, expectedValue);        // Use EXPECT_THAT(result, Eq(expectedValue))
EXPECT_DOUBLE_EQ(result, expectedDouble); // Use EXPECT_THAT(result, DoubleEq(expectedDouble))
EXPECT_THROW(func(), exception);         // Use EXPECT_THAT(lambda, Throws<exception>())
```

**Required matcher imports:**
```cpp
// Third-party headers
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::DoubleEq;
using ::testing::Eq;
using ::testing::Throws;
```

**Benefits of EXPECT_THAT with matchers:**
- **Composability**: Matchers can be combined with `AllOf`, `AnyOf`, `Not`
- **Readability**: More expressive and English-like syntax
- **Extensibility**: Custom matchers for domain-specific assertions
- **Better error messages**: More descriptive failure output
- **Consistency**: Unified assertion style across all test types

### Testing Best Practices
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

### Test Data Management
```cpp
// Good: Use meaningful constants
TEST_F(CalculatorTest, Add_LargeNumbers_ReturnsCorrectSum) {
  // Arrange
  const int firstLargeNumber = 999999;
  const int secondLargeNumber = 888888;
  const int expectedSum = 1888887;

  // Act
  int result = calculator.add(firstLargeNumber, secondLargeNumber);

  // Assert
  EXPECT_THAT(result, Eq(expectedSum));
}

// Avoid: Magic numbers without context
TEST_F(CalculatorTest, Add_Numbers_ReturnsSum) {
  EXPECT_THAT(calculator.add(42, 17), Eq(59)); // What's special about 42 and 17?
}
```

## Benchmarking Guidelines

### Benchmark Naming Convention (MANDATORY)
Benchmark functions MUST be prefixed with `BM_` followed by a descriptive name:
```cpp
static void BM_Addition(benchmark::State& state)
static void BM_LargeVectorSort(benchmark::State& state)
static void BM_DatabaseQuery_WithIndex(benchmark::State& state)
```

### Benchmark Structure
- Use `benchmark::DoNotOptimize()` to prevent compiler optimizations from eliminating the code being measured
- Initialize test data outside the timing loop when possible
- Use the `state` parameter to control iterations

```cpp
static void BM_Addition(benchmark::State& state) {
  // Arrange (outside timing loop)
  Calculator calc;

  // Act (timed loop)
  for (auto _ : state) {
    benchmark::DoNotOptimize(calc.add(42, 17));
  }
}
```

### Parameterized Benchmarks
Use `Args()` to test different input sizes or scenarios:
```cpp
BENCHMARK(BM_VectorSearch)->Args({100})->Args({1000})->Args({10000});
BENCHMARK(BM_StringProcessing)->Args({8, 32})->Args({64, 128});
```

### Benchmark Best Practices
- **Measure one thing**: Each benchmark should focus on a single operation or algorithm
- **Avoid setup overhead**: Initialize expensive resources outside the timing loop
- **Use realistic data**: Test with data representative of actual usage
- **Multiple runs**: Let the framework handle multiple iterations for statistical accuracy
- **State management**: Reset state between iterations if needed using `state.PauseTiming()` and `state.ResumeTiming()`

### Complex Benchmark Example
```cpp
static void BM_ComplexOperation_WithSetup(benchmark::State& state) {
  // Expensive setup outside timing loop
  std::vector<int> data(state.range(0));
  std::iota(data.begin(), data.end(), 1);

  for (auto _ : state) {
    state.PauseTiming();
    // Reset state if needed
    std::shuffle(data.begin(), data.end(), std::mt19937{42});
    state.ResumeTiming();

    // The operation being benchmarked
    benchmark::DoNotOptimize(std::sort(data.begin(), data.end()));
  }

  // Optional: Set bytes processed or items processed
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_ComplexOperation_WithSetup)->Range(1000, 100000);
```
