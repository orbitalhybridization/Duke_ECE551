#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // error check num command line args
  if (argc != 2) {
    fprintf(stderr, "Correct usage: ./story-step1 [filename]");
    exit(EXIT_FAILURE);
  }

  // open file for read
  processStoryTemplate(argv[1], NULL, 0);
}
