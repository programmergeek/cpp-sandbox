#include "math.h"

int subtract(int a, int b) { return a - b; }

int pow(int a, int b) {
  int x{1};
  for (int i = 0; i < b; i++) {
    x *= a;
  }

  return x;
}
