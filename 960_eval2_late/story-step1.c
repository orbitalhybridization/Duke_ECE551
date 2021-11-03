#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

void readLines(FILE * f) {
  // read line by line
  size_t sz;
  char * line = NULL;
  while (getline(&line, &sz, f) >= 0) {
    char * parsedLine = parseLine(line);
    printf("%s",
           parsedLine);  // go through each line and parse the underscores, and print!
    free(parsedLine);
  }
  free(line);
}

int main(int argc, char ** argv) {
  // error check num command line args
  if (argc != 2) {
    fprintf(stderr, "Correct usage: ./story-step1 [filename]");
    exit(EXIT_FAILURE);
  }

  // open file for read
  FILE * f = fopen(argv[1], "r");
  // error check file opened correctly
  if (f == NULL) {
    fprintf(stderr, "Could not open file!");
    exit(EXIT_FAILURE);
  }

  readLines(f);  // read file line by line
  // close file
  fclose(f);
}
