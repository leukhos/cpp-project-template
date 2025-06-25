#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calculator;
};

TEST_F(CalculatorTest, AddPositiveNumbers) {
    EXPECT_EQ(calculator.add(2, 3), 5);
    EXPECT_EQ(calculator.add(10, 15), 25);
}

TEST_F(CalculatorTest, AddNegativeNumbers) {
    EXPECT_EQ(calculator.add(-2, -3), -5);
    EXPECT_EQ(calculator.add(-10, 5), -5);
}

TEST_F(CalculatorTest, SubtractNumbers) {
    EXPECT_EQ(calculator.subtract(5, 3), 2);
    EXPECT_EQ(calculator.subtract(10, 15), -5);
}

TEST_F(CalculatorTest, MultiplyNumbers) {
    EXPECT_EQ(calculator.multiply(3, 4), 12);
    EXPECT_EQ(calculator.multiply(-2, 5), -10);
    EXPECT_EQ(calculator.multiply(0, 100), 0);
}

TEST_F(CalculatorTest, DivideNumbers) {
    EXPECT_DOUBLE_EQ(calculator.divide(10, 2), 5.0);
    EXPECT_DOUBLE_EQ(calculator.divide(7, 2), 3.5);
    EXPECT_DOUBLE_EQ(calculator.divide(-10, 2), -5.0);
}

TEST_F(CalculatorTest, DivideByZeroThrowsException) {
    EXPECT_THROW(calculator.divide(10, 0), std::invalid_argument);
}

class MockCalculator {
public:
    MOCK_METHOD(int, add, (int firstValue, int secondValue));
    MOCK_METHOD(int, subtract, (int firstValue, int secondValue));
};

TEST(MockCalculatorTest, MockExample) {
    MockCalculator mockCalculator;
    
    EXPECT_CALL(mockCalculator, add(2, 3))
        .WillOnce(::testing::Return(5));
    
    EXPECT_EQ(mockCalculator.add(2, 3), 5);
}