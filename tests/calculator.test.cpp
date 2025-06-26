// First-party headers
#include "calculator.h"

// Third-party headers
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class CalculatorTest : public ::testing::Test
{
  protected:
    Calculator calculator;
};

TEST_F(CalculatorTest, Add_PositiveNumbers_ReturnsCorrectSum)
{
    // Arrange
    int firstValue = 2;
    int secondValue = 3;
    int expectedSum = 5;
    
    // Act
    int result = calculator.add(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedSum);
}

TEST_F(CalculatorTest, Add_LargePositiveNumbers_ReturnsCorrectSum)
{
    // Arrange
    int firstValue = 10;
    int secondValue = 15;
    int expectedSum = 25;
    
    // Act
    int result = calculator.add(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedSum);
}

TEST_F(CalculatorTest, Add_NegativeNumbers_ReturnsCorrectSum)
{
    // Arrange
    int firstValue = -2;
    int secondValue = -3;
    int expectedSum = -5;
    
    // Act
    int result = calculator.add(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedSum);
}

TEST_F(CalculatorTest, Add_MixedSignNumbers_ReturnsCorrectSum)
{
    // Arrange
    int firstValue = -10;
    int secondValue = 5;
    int expectedSum = -5;
    
    // Act
    int result = calculator.add(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedSum);
}

TEST_F(CalculatorTest, Subtract_PositiveNumbers_ReturnsCorrectDifference)
{
    // Arrange
    int firstValue = 5;
    int secondValue = 3;
    int expectedDifference = 2;
    
    // Act
    int result = calculator.subtract(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedDifference);
}

TEST_F(CalculatorTest, Subtract_ResultingInNegative_ReturnsCorrectDifference)
{
    // Arrange
    int firstValue = 10;
    int secondValue = 15;
    int expectedDifference = -5;
    
    // Act
    int result = calculator.subtract(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedDifference);
}

TEST_F(CalculatorTest, Multiply_PositiveNumbers_ReturnsCorrectProduct)
{
    // Arrange
    int firstValue = 3;
    int secondValue = 4;
    int expectedProduct = 12;
    
    // Act
    int result = calculator.multiply(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedProduct);
}

TEST_F(CalculatorTest, Multiply_NegativeAndPositive_ReturnsCorrectProduct)
{
    // Arrange
    int firstValue = -2;
    int secondValue = 5;
    int expectedProduct = -10;
    
    // Act
    int result = calculator.multiply(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedProduct);
}

TEST_F(CalculatorTest, Multiply_WithZero_ReturnsZero)
{
    // Arrange
    int firstValue = 0;
    int secondValue = 100;
    int expectedProduct = 0;
    
    // Act
    int result = calculator.multiply(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedProduct);
}

TEST_F(CalculatorTest, Divide_EvenDivision_ReturnsCorrectQuotient)
{
    // Arrange
    int firstValue = 10;
    int secondValue = 2;
    double expectedQuotient = 5.0;
    
    // Act
    double result = calculator.divide(firstValue, secondValue);
    
    // Assert
    EXPECT_DOUBLE_EQ(result, expectedQuotient);
}

TEST_F(CalculatorTest, Divide_WithRemainder_ReturnsCorrectQuotient)
{
    // Arrange
    int firstValue = 7;
    int secondValue = 2;
    double expectedQuotient = 3.5;
    
    // Act
    double result = calculator.divide(firstValue, secondValue);
    
    // Assert
    EXPECT_DOUBLE_EQ(result, expectedQuotient);
}

TEST_F(CalculatorTest, Divide_NegativeNumber_ReturnsCorrectQuotient)
{
    // Arrange
    int firstValue = -10;
    int secondValue = 2;
    double expectedQuotient = -5.0;
    
    // Act
    double result = calculator.divide(firstValue, secondValue);
    
    // Assert
    EXPECT_DOUBLE_EQ(result, expectedQuotient);
}

TEST_F(CalculatorTest, Divide_ByZero_ThrowsInvalidArgumentException)
{
    // Arrange
    int firstValue = 10;
    int secondValue = 0;
    
    // Act & Assert
    EXPECT_THROW(calculator.divide(firstValue, secondValue), std::invalid_argument);
}

class MockCalculator
{
  public:
    MOCK_METHOD(int, add, (int firstValue, int secondValue));
    MOCK_METHOD(int, subtract, (int firstValue, int secondValue));
};

TEST(MockCalculatorTest, Add_WithMock_ReturnsExpectedValue)
{
    // Arrange
    MockCalculator mockCalculator;
    int firstValue = 2;
    int secondValue = 3;
    int expectedResult = 5;
    
    EXPECT_CALL(mockCalculator, add(firstValue, secondValue))
        .WillOnce(::testing::Return(expectedResult));
    
    // Act
    int result = mockCalculator.add(firstValue, secondValue);
    
    // Assert
    EXPECT_EQ(result, expectedResult);
}