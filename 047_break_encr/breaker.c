#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int array_max(int * array,
              int size) {  // take an array and return index of largest value
  int max = 0;
  for (int i = 0; i < size; i++) {
    if (array[i] > max) {
      max = i;
    }
  }
  return max;
}

int abs_val(int left, int right) {  // calculate absolute value of two ints subtracted
  if ((left - right) < 0) {
    return (left - right) * (-1);
  }

  else {
    return (left - right);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {  // need 2 arguments
    fprintf(stderr, "Usage: ./breaker [filename]\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");  // open file

  int char_count[26] = {0};  // set up character count, init to 0

  int c;
  while ((c = fgetc(f)) != EOF) {  // loop through and add to chars
    if (isalpha(c)) {
      c = tolower(c);           // make lowercase to make our lives easier
      char_count[c - 97] += 1;  // update frequency count
    }
  }
  int e_guess = array_max(char_count, 26);
  // translate e_guess
  printf("I think e is encrypted as the letter %c. Or in ASCII, %d.\n",
         e_guess + 97,
         e_guess + 97);
  int encryption_key = e_guess - 4;

  while (encryption_key < 0) {
    encryption_key += 26;
  }

  fprintf(stdout, "%d\n", encryption_key);  // print guess and return
  return EXIT_SUCCESS;
}
