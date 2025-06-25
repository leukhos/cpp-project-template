#pragma once

#include <stdexcept>

class Calculator
{
  public:
    int add(int firstValue, int secondValue);
    int subtract(int firstValue, int secondValue);
    int multiply(int firstValue, int secondValue);
    double divide(int firstValue, int secondValue);
};