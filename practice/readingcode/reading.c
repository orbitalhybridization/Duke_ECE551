#include <stdio.h>
#include <stdlib.h>

void f(int v, int * p, int ** q) {
  v = v % 2;
  int temp = (v + 1) % 2;
  p[v] = p[temp];
  p = q[v];
  q[v] = q[temp];
  q[temp] = p;
}

int main(void) {
  int * data[2];
  for (int i = 0; i < 2; i++) {
    data[i] = malloc(2 * sizeof(*data[i]));
    for (int j = 0; j < 2; j++) {
      data[i][j] = i * 2 + j;
    }
  }

  f(data[0][0], data[1], data);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("data[%d][%d]=%d\n", i, j, data[i][j]);
    }
    free(data[i]);
  }
  return EXIT_SUCCESS;
}
