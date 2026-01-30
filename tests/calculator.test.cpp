// First-party headers
#include "calculator/calculator.h"

// Third-party headers
#include <doctest/doctest.h>
#include <doctest/trompeloeil.hpp>

// Functional/Integration tests for public API

TEST_CASE("Calculator - functional test for basic arithmetic workflow") {
  // This test simulates a real-world usage scenario
  Calculator calculator;

  SUBCASE("performing multiple operations in sequence") {
    // Arrange
    int initial_value = 100;
    int add_amount = 50;
    int subtract_amount = 30;
    int multiply_factor = 2;

    // Act - Simulate a calculation workflow
    int after_add = calculator.add(initial_value, add_amount);
    int after_subtract = calculator.subtract(after_add, subtract_amount);
    int final_result = calculator.multiply(after_subtract, multiply_factor);

    // Assert - Verify the final result
    CHECK(final_result == 240); // (100 + 50 - 30) * 2
  }

  SUBCASE("calculating average using division") {
    // Arrange - Sum of values
    int sum = calculator.add(10, 20);
    sum = calculator.add(sum, 30);
    int count = 3;

    // Act - Calculate average
    double average = calculator.divide(sum, count);

    // Assert
    CHECK(average == doctest::Approx(20.0));
  }
}

TEST_CASE("Calculator - functional test for error handling") {
  Calculator calculator;

  SUBCASE("division by zero in a calculation chain") {
    // Arrange
    int numerator = calculator.multiply(5, 4); // 20

    // Act & Assert - Verify exception is thrown
    CHECK_THROWS_AS(calculator.divide(numerator, 0), std::invalid_argument);
  }

  SUBCASE("recovery after exception") {
    // Arrange
    Calculator calc;

    // Act - Try division by zero
    try {
      calc.divide(10, 0);
    } catch (const std::invalid_argument&) {
      // Exception caught, calculator should still work
    }

    // Assert - Calculator still functional after exception
    int result = calc.add(5, 5);
    CHECK(result == 10);
  }
}

TEST_CASE("Calculator - functional test for edge cases") {
  Calculator calculator;

  SUBCASE("large number calculations") {
    // Arrange
    int large_num = 1000000;
    int small_num = 1;

    // Act
    int add_result = calculator.add(large_num, small_num);
    int subtract_result = calculator.subtract(large_num, small_num);

    // Assert
    CHECK(add_result == 1000001);
    CHECK(subtract_result == 999999);
  }

  SUBCASE("operations with negative results") {
    // Arrange & Act
    int result1 = calculator.subtract(5, 10);
    int result2 = calculator.multiply(-3, 4);
    double result3 = calculator.divide(-20, 4);

    // Assert
    CHECK(result1 == -5);
    CHECK(result2 == -12);
    CHECK(result3 == doctest::Approx(-5.0));
  }
}

TEST_CASE("Calculator - functional test for precision") {
  Calculator calculator;

  SUBCASE("division precision with integer inputs") {
    // Arrange
    int numerator = 1;
    int denominator = 3;

    // Act
    double result = calculator.divide(numerator, denominator);

    // Assert - Verify floating-point precision
    CHECK(result == doctest::Approx(0.333333).epsilon(0.000001));
  }

  SUBCASE("division of primes produces exact floating-point") {
    // Arrange
    int numerator = 7;
    int denominator = 2;

    // Act
    double result = calculator.divide(numerator, denominator);

    // Assert
    CHECK(result == doctest::Approx(3.5));
  }
}

// Service interface for dependency injection and mocking
class ICalculator {
public:
  virtual ~ICalculator() = default;
  virtual int add(int first_value, int second_value) = 0;
  virtual int subtract(int first_value, int second_value) = 0;
};

// Mock implementation using Trompeloeil
class MockCalculator : public ICalculator {
public:
  MAKE_MOCK2(add, int(int, int), override);
  MAKE_MOCK2(subtract, int(int, int), override);
};

TEST_CASE("MockCalculator - functional test with mocking") {
  // Functional test demonstrating how to mock dependencies
  // in integration scenarios

  SUBCASE("mocking calculator for dependency injection") {
    // Arrange
    MockCalculator mock_calculator;
    int first_value = 2;
    int second_value = 3;
    int expected_result = 5;

    REQUIRE_CALL(mock_calculator, add(first_value, second_value))
        .RETURN(expected_result);

    // Act - Simulate using the calculator through an interface
    int result = mock_calculator.add(first_value, second_value);

    // Assert
    CHECK(result == expected_result);
  }

  SUBCASE("verifying call counts in workflow") {
    // Arrange
    MockCalculator mock_calculator;

    REQUIRE_CALL(mock_calculator, add(trompeloeil::_, trompeloeil::_))
        .TIMES(2)
        .RETURN(0);

    // Act - Simulate multiple operations
    mock_calculator.add(1, 2);
    mock_calculator.add(3, 4);

    // Assert - Trompeloeil verifies the call count automatically
  }
}
