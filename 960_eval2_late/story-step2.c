#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // error check num command line args
  if (argc != 2) {
    fprintf(stderr, "Correct usage: ./story-step2 [filename]");
    exit(EXIT_FAILURE);
  }

  // get categories from file
  catarray_t * categories = parseCategoryFile(argv[1]);
  // print them!
  printWords(categories);

  // free associated memory
  freeCatArray(categories);
}
