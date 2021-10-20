#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char * test_string = "This _is_ a test_ string!";
  char * token;
  char * delim = "_";
  int i = 1;
  char * saveptr;
  token = strtok_r(test_string, delim, &saveptr);
  printf("Call %d: %s.\n", i, token);
  //   while ((token = strtok_r(NULL, "_")) != NULL) {
  //    printf("Call %d: %s.\n", i, token);
  //    i++;
  //  }
  return 1;
}
