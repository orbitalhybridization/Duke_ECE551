#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);  // prototype for function to test

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned int ans = power(x, y);
  if (ans != expected_ans) {
    printf("Answer (%d) not equal to expected answer (%d)\n", ans, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  // this is where we put our test cases
  run_check(2, 2, 4);            // test a normal case
  run_check(1, 1, 1);            // an edge case
  run_check(0, 1, 0);            // another edge case
  run_check(10, 2, 100);         // 10  case
  run_check(1, 0, 1);            // another edge case
  run_check(-1, 1, 4294967295);  // negative case (interpret as large number)
  run_check(2, 10, 1024);        // ^10 case
  run_check('*', 2, 1764);       // ascii case

  run_check(2, 32, 0);  // overflow case

  run_check(2.2, 3, 8);  // float case

  run_check(0, 0, 1);

  float c = 2.2;
  run_check(c, 2, 4);
  printf("All tests passed!");
  return EXIT_SUCCESS;
}
