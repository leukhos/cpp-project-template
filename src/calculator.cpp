// First-party headers
#include "calculator/calculator.h"

// Standard library headers
#include <stdexcept>

int Calculator::add(int firstValue, int secondValue) {
  return firstValue + secondValue;
}

int Calculator::subtract(int firstValue, int secondValue) {
  return firstValue - secondValue;
}

int Calculator::multiply(int firstValue, int secondValue) {
  return firstValue * secondValue;
}

double Calculator::divide(int firstValue, int secondValue) {
  if (secondValue == 0) {
    throw std::invalid_argument("Division by zero");
  }

  return static_cast<double>(firstValue) / secondValue;
}