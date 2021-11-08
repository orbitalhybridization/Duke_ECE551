#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // check command line arguments
  if (((argc != 3) && (argc != 4)) || ((strcmp("-n", argv[1]) != 0) && (argc == 4))) {
    fprintf(stderr,
            "Correct usage: ./story-step3 [optional: -n] [categories file] [story "
            "template file]");
    exit(EXIT_FAILURE);
  }

  int no_reuse = 0;
  int category_file = 1;
  int template = 2;
  // check for reuse flag. if so, shift other args too
  if (argc == 4) {
    no_reuse = 1;
    category_file = 2;
    template = 3;
  }

  // collect categories from file
  catarray_t * categories = parseCategoryFile(argv[category_file]);

  // print lines of story
  processStoryTemplate(argv[template], categories, no_reuse);

  return EXIT_SUCCESS;
}
