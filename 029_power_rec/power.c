#include <stdint.h>
#include <stdio.h>

unsigned power(unsigned x, unsigned y) {
  if (y == 1) {
    return x;
  }

  else if (y == 0) {
    return 1;
  }

  else {
    return x * power(x, y - 1);
  }  // recursive call
}
