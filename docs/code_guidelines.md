# C++ Code Guidelines

This document provides comprehensive coding standards for this C++ project.

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
`BM_[Component]_[Operation]_[Scenario]_[Parameters]`
- Example: `BM_Vector_PushBack_Empty`, `BM_Sort_QuickSort_Random_1K`

### Formatting
- LLVM style (clang-format)
- 2-space indentation
- Run: `clang-format -i src/**/*.{cpp,h} tests/**/*.{cpp,h} benchmarks/**/*.cpp`

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

### Rationale (EXPLANATION)

This header organization ensures:
- **Dependency clarity**: All dependencies are explicit and visible
- **Build reliability**: No hidden dependencies through transitive inclusion
- **Maintainability**: Easy to identify what each file depends on
- **Compilation speed**: Precompiled headers first, followed by logical dependency order

## Testing Guidelines (CRITICAL)

### Test Naming Convention (MANDATORY FORMAT)
Test names MUST follow: `MethodName_Scenario_ExpectedBehavior`

**Three required components:**
- **Method being tested**: Exact method or functionality under test
- **Scenario**: Specific conditions or input that triggers the test case  
- **Expected behavior**: Anticipated outcome or result

**Examples:**
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

### Test Organization (GUIDELINES)
- **Use test fixtures**: Use `TEST_F` for tests that share setup/teardown
- **Group related tests**: Keep related tests in the same test class
- **Descriptive class names**: Use test class names ending with "Test"
- **Mock placement**: Place mock classes immediately after the main test class

### Exception Testing (GUIDELINES)
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

### Test Data Management (EXAMPLES)

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

## Benchmarking Guidelines (GUIDELINES)

### Benchmark Naming Convention (MANDATORY FORMAT)

Benchmark functions MUST follow this structure: `BM_[Component]_[Operation]_[Scenario]_[Parameters]`

**Four required components:**
1. **BM_** - Standard prefix indicating this is a benchmark function
2. **Component** - The class, module, or subsystem being benchmarked
3. **Operation** - The specific method or functionality being benchmarked
4. **Scenario** - The test conditions or data characteristics
5. **Parameters** - Optional size, type, or configuration details

### Naming Patterns and Examples (EXAMPLES)

#### Basic Structure
```cpp
// Pattern: BM_Component_Operation
void BM_Vector_PushBack(benchmark::State& state) { /* ... */ }
void BM_Map_Insert(benchmark::State& state) { /* ... */ }
void BM_String_Find(benchmark::State& state) { /* ... */ }
```

#### With Scenarios
```cpp
// Pattern: BM_Component_Operation_Scenario
void BM_Vector_PushBack_Empty(benchmark::State& state) { /* ... */ }
void BM_Vector_PushBack_Preallocated(benchmark::State& state) { /* ... */ }
void BM_Map_Insert_Sequential(benchmark::State& state) { /* ... */ }
void BM_Map_Insert_Random(benchmark::State& state) { /* ... */ }
```

#### With Parameters
```cpp
// Pattern: BM_Component_Operation_Scenario_Parameters
void BM_Sort_QuickSort_Random_Small(benchmark::State& state) { /* ... */ }
void BM_Sort_QuickSort_Random_Large(benchmark::State& state) { /* ... */ }
void BM_Hash_Lookup_Uniform_1K(benchmark::State& state) { /* ... */ }
void BM_Hash_Lookup_Skewed_10K(benchmark::State& state) { /* ... */ }
```

### Specific Naming Conventions (EXAMPLES)

#### Data Structure Benchmarks
```cpp
void BM_Vector_Access_Sequential(benchmark::State& state);
void BM_Vector_Access_Random(benchmark::State& state);
void BM_List_Traverse_Forward(benchmark::State& state);
void BM_HashMap_Lookup_Hit(benchmark::State& state);
void BM_HashMap_Lookup_Miss(benchmark::State& state);
```

#### Algorithm Benchmarks
```cpp
void BM_Sort_MergeSort_Sorted(benchmark::State& state);
void BM_Sort_MergeSort_Reverse(benchmark::State& state);
void BM_Search_BinarySearch_Found(benchmark::State& state);
void BM_Search_LinearSearch_NotFound(benchmark::State& state);
```

#### I/O and System Benchmarks
```cpp
void BM_File_Read_Sequential_4KB(benchmark::State& state);
void BM_File_Write_Random_1MB(benchmark::State& state);
void BM_Network_TCP_Send_Small(benchmark::State& state);
void BM_Memory_Allocate_Aligned(benchmark::State& state);
```

### Parameter-Driven Benchmarks (GUIDELINES)

For benchmarks that test multiple sizes or configurations, use Google Benchmark's parameter features:

```cpp
// Use descriptive base names with parameters
static void BM_Vector_PushBack(benchmark::State& state) {
  auto size = state.range(0);
  // Implementation...
}
BENCHMARK(BM_Vector_PushBack)->Range(8, 8<<10);

// Or with custom arguments
static void BM_Matrix_Multiply(benchmark::State& state) {
  auto rows = state.range(0);
  auto cols = state.range(1);
  // Implementation...
}
BENCHMARK(BM_Matrix_Multiply)->Args({64, 64})->Args({128, 128})->Args({256, 256});
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

### Size Indicators (GUIDELINES)
```cpp
// Use standard size indicators
void BM_Container_Operation_1K(benchmark::State& state);   // ~1,000 elements
void BM_Container_Operation_1M(benchmark::State& state);   // ~1,000,000 elements
void BM_Buffer_Copy_4KB(benchmark::State& state);          // 4 kilobytes
void BM_Cache_Lookup_L1(benchmark::State& state);          // L1 cache size
```

### Example Benchmark Suite (EXAMPLES)

```cpp
// String processing benchmarks
void BM_String_Find_Short_Found(benchmark::State& state);
void BM_String_Find_Short_NotFound(benchmark::State& state);
void BM_String_Find_Long_Found(benchmark::State& state);
void BM_String_Replace_Single(benchmark::State& state);
void BM_String_Replace_Multiple(benchmark::State& state);

// Container benchmarks
void BM_Vector_Insert_Front(benchmark::State& state);
void BM_Vector_Insert_Middle(benchmark::State& state);
void BM_Vector_Insert_Back(benchmark::State& state);
void BM_Deque_Insert_Front(benchmark::State& state);
void BM_Deque_Insert_Back(benchmark::State& state);

// Algorithm benchmarks
void BM_Sort_IntroSort_Random_1K(benchmark::State& state);
void BM_Sort_IntroSort_Sorted_1K(benchmark::State& state);
void BM_Sort_IntroSort_Reverse_1K(benchmark::State& state);
```

### Registration Patterns (GUIDELINES)

When registering benchmarks, maintain consistency:

```cpp
// Simple registration
BENCHMARK(BM_Vector_PushBack);

// With parameters
BENCHMARK(BM_Sort_QuickSort)->Range(1<<10, 1<<18);

// With custom arguments
BENCHMARK(BM_Hash_Insert)->Args({1000, 75})->Args({10000, 90});

// With time units
BENCHMARK(BM_Algorithm_Process)->Unit(benchmark::kMicrosecond);
```

Following these guidelines will make your benchmarks more maintainable, easier to understand, and consistent with community standards.
