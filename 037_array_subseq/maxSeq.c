#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t longest = 1;
  unsigned count = 1;
  for (unsigned i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {  // increase count if we found more satisfying sequence
      count += 1;
    }
    if (count > longest) {
      longest = count;
    }
    if (array[i] >= array[i + 1]) {
      count = 1;  // set new longest if record broken
    }
  }
  return longest;
}
