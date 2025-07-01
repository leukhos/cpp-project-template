// First-party headers
#include "calculator.h"

// Standard library headers
#include <iostream>

int main() {
  Calculator calc;

  std::cout << "Calculator Demo" << std::endl;
  std::cout << "5 + 3 = " << calc.add(5, 3) << std::endl;
  std::cout << "5 - 3 = " << calc.subtract(5, 3) << std::endl;
  std::cout << "5 * 3 = " << calc.multiply(5, 3) << std::endl;
  std::cout << "5 / 3 = " << calc.divide(5, 3) << std::endl;

  return 0;
}