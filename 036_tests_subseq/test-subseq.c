#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);  // first declare prototype of function

void run_test(int * array, size_t n, size_t expected_ans) {
  size_t ans = maxSeq(array, n);
  if (ans != expected_ans) {
    printf("Answer (%lu) not equal to expected answer (%lu)!\n", ans, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[1] = {1};  // test size 1
  run_test(array1, 1, 1);

  int array2[1] = {0};  // test size 0
  run_test(array2, 1, 1);

  int array3[12] = {1, 2, 3, 4, 3, 2, 1, 2, 1, 2, 1, 2};  // test a normal size case
  run_test(array3, 12, 4);

  int array4[6] = {1, 1, 1, 1, 1, 1};  // test flat line, no increase
  run_test(array4, 6, 1);

  int array5[4] = {4, 3, 2, 1};  // test strictly decreasing
  run_test(array5, 4, 1);

  // test negative
  int array6[4] = {-2, -1, 0, 1};
  run_test(array6, 4, 4);

  // test skipping multiples
  int array7[6] = {0, 2, 4, 6, 7, 8};
  run_test(array7, 6, 6);

  // test slight increase but bigger one later
  int array8[8] = {9, 10, -2, -1, 0, 1, 2, 3};
  run_test(array8, 8, 6);

  // test discontiguous
  int array9[5] = {1, 0, 3, 0, 4};
  run_test(array9, 5, 2);

  // test negative decreasing
  int array10[5] = {-1, -2, -3, -4, -5};
  run_test(array10, 5, 1);

  // test larger discontiguous
  int array11[6] = {1, 2, 4, 4, 6, 6};
  run_test(array11, 6, 3);

  //test decrease then increase
  int array12[6] = {5, 4, 3, 2, 3, 4};
  run_test(array12, 6, 3);

  //test size 0
  int array13[3] = {1, 2, 3};
  run_test(array13, 0, 0);

  printf("All tests passed!");
  return EXIT_SUCCESS;
}
