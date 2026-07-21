#include "add.h"
#include "math.h"
#include <iostream>

#define GREETING "Hello World"

int main() {
  std::cout << GREETING << std::endl;
  int x{5};
  int y{4};
  std::cout << add(x, y) << std::endl;
  std::cout << subtract(x, y) << std::endl;
  std::cout << pow(x, y) << std::endl;
  return 0;
}
