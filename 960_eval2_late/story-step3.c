#include <stdio.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // check command line arguments
  if (argc != 3) {
    fprintf(stderr,
            "Correct usage: ./story-step3 [categories file] [story template file]");
    exit(EXIT_FAILURE);
  }

  // collect categories from file
  catarray_t * categories = parseCategoryFile(argv[1]);

  // print lines of story
  processStoryTemplate(argv[2], categories);

  return EXIT_SUCCESS;
}
