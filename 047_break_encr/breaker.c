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
      c = tolower(c);            // make lowercase to make our lives easier
      char_count[c - 'a'] += 1;  // update frequency count
    }
  }

  int encryption_key;
  int e_guess = array_max(char_count, 26);
  char e_guess_char = e_guess + 'a';  // translate to char
  // translate e_guess
  if (e_guess_char < 'e') {
    encryption_key = e_guess_char - 'e';
  }

  else {
    encryption_key = e_guess_char - 'e' + 26;
  }

  fprintf(stdout, "%d\n", encryption_key);  // print guess and return
  return EXIT_SUCCESS;
}
