#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int array_max(int * array, int size) {  // take an array and return index of largest value
  int max = 0;
  for (int i = 0; i < size; i++) {
    if (array[i] > max) {
      max = i;
    }
  }
  return max;
}

int main(int argc, char ** argv) {
  if (argc != 2) {  // need 2 arguments
    fprintf(stderr, "Usage: ./breaker [filename]\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");  // open file

  int char_count[26] = {0};  // set up character count, init to 0

  int c;
  while ((c = fgetc(f)) != EOF) {  // loop through
    if (isalpha(c)) {
      c = tolower(c);      // make lowercase to make our lives easier
      c -= 97;             // move out of ascii
      char_count[c] += 1;  // update frequency count
    }
  }
  int e_guess = array_max(char_count, 26);

  fprintf(stdout, "%d\n", e_guess - 101);  // print guess and return
}
