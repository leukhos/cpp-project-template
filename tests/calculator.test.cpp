// First-party headers
#include "calculator/calculator.h"

// Third-party headers
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::DoubleEq;
using ::testing::Eq;

class CalculatorTest : public ::testing::Test {
protected:
  Calculator calculator;
};

TEST_F(CalculatorTest, Add_PositiveNumbers_ReturnsCorrectSum) {
  // Arrange
  int first_value = 2;
  int second_value = 3;
  int expected_sum = 5;

  // Act
  int result = calculator.add(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_sum));
}

TEST_F(CalculatorTest, Add_LargePositiveNumbers_ReturnsCorrectSum) {
  // Arrange
  int first_value = 10;
  int second_value = 15;
  int expected_sum = 25;

  // Act
  int result = calculator.add(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_sum));
}

TEST_F(CalculatorTest, Add_NegativeNumbers_ReturnsCorrectSum) {
  // Arrange
  int first_value = -2;
  int second_value = -3;
  int expected_sum = -5;

  // Act
  int result = calculator.add(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_sum));
}

TEST_F(CalculatorTest, Add_MixedSignNumbers_ReturnsCorrectSum) {
  // Arrange
  int first_value = -10;
  int second_value = 5;
  int expected_sum = -5;

  // Act
  int result = calculator.add(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_sum));
}

TEST_F(CalculatorTest, Subtract_PositiveNumbers_ReturnsCorrectDifference) {
  // Arrange
  int first_value = 5;
  int second_value = 3;
  int expected_difference = 2;

  // Act
  int result = calculator.subtract(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_difference));
}

TEST_F(CalculatorTest, Subtract_ResultingInNegative_ReturnsCorrectDifference) {
  // Arrange
  int first_value = 10;
  int second_value = 15;
  int expected_difference = -5;

  // Act
  int result = calculator.subtract(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_difference));
}

TEST_F(CalculatorTest, Multiply_PositiveNumbers_ReturnsCorrectProduct) {
  // Arrange
  int first_value = 3;
  int second_value = 4;
  int expected_product = 12;

  // Act
  int result = calculator.multiply(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_product));
}

TEST_F(CalculatorTest, Multiply_NegativeAndPositive_ReturnsCorrectProduct) {
  // Arrange
  int first_value = -2;
  int second_value = 5;
  int expected_product = -10;

  // Act
  int result = calculator.multiply(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_product));
}

TEST_F(CalculatorTest, Multiply_WithZero_ReturnsZero) {
  // Arrange
  int first_value = 0;
  int second_value = 100;
  int expected_product = 0;

  // Act
  int result = calculator.multiply(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_product));
}

TEST_F(CalculatorTest, Divide_EvenDivision_ReturnsCorrectQuotient) {
  // Arrange
  int first_value = 10;
  int second_value = 2;
  double expected_quotient = 5.0;

  // Act
  double result = calculator.divide(first_value, second_value);

  // Assert
  EXPECT_THAT(result, DoubleEq(expected_quotient));
}

TEST_F(CalculatorTest, Divide_WithRemainder_ReturnsCorrectQuotient) {
  // Arrange
  int first_value = 7;
  int second_value = 2;
  double expected_quotient = 3.5;

  // Act
  double result = calculator.divide(first_value, second_value);

  // Assert
  EXPECT_THAT(result, DoubleEq(expected_quotient));
}

TEST_F(CalculatorTest, Divide_NegativeNumber_ReturnsCorrectQuotient) {
  // Arrange
  int first_value = -10;
  int second_value = 2;
  double expected_quotient = -5.0;

  // Act
  double result = calculator.divide(first_value, second_value);

  // Assert
  EXPECT_THAT(result, DoubleEq(expected_quotient));
}

TEST_F(CalculatorTest, Divide_ByZero_ThrowsInvalidArgumentException) {
  // Arrange
  int first_value = 10;
  int second_value = 0;

  // Act & Assert
  EXPECT_THROW(calculator.divide(first_value, second_value),
               std::invalid_argument);
}

class MockCalculator {
public:
  MOCK_METHOD(int, add, (int first_value, int second_value));
  MOCK_METHOD(int, subtract, (int first_value, int second_value));
};

TEST(MockCalculatorTest, Add_WithMock_ReturnsExpectedValue) {
  // Arrange
  MockCalculator mock_calculator;
  int first_value = 2;
  int second_value = 3;
  int expected_result = 5;

  EXPECT_CALL(mock_calculator, add(first_value, second_value))
      .WillOnce(::testing::Return(expected_result));

  // Act
  int result = mock_calculator.add(first_value, second_value);

  // Assert
  EXPECT_THAT(result, Eq(expected_result));
}