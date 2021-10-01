#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readLines(FILE * input) {
  char ** lines = NULL;  // create container for all lines
  size_t size_array = 0;
  size_t sz;
  char * current_line = NULL;

  if (input == NULL) {
    fprintf(stderr, "Input invalid.");
    exit(EXIT_FAILURE);
  }

  while (getline(&current_line, &sz, input) >= 0) {  // read from command line input
    lines = realloc(lines, (size_array + 1) * sizeof(*lines));  // resize array of strings
    lines[size_array] = current_line;
    current_line =
        NULL;  // make current line point to a new line from get line rather than adding to buffer
    size_array++;
  }
  free(current_line);           // we don't need current line anymore
  sortData(lines, size_array);  // sort lines of input

  for (size_t index = 0; index < size_array; index++) {
    printf("%s", lines[index]);  // print results
    free(lines[index]);          // free memory
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  if (argc == 1) {  // if we have no args, read from stdin
    if (stdin == NULL) {
      fprintf(stderr, "Nothing in stdin!");
      exit(EXIT_FAILURE);
    }
    else {
      readLines(stdin);
    }
  }

  else {                              // otherwise treat as file
    for (int i = 1; i < argc; i++) {  // loop through all args
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {  // case: we couldn't read the file!
        fprintf(stderr, "File could not be read!");
        exit(EXIT_FAILURE);
      }
      else {
        readLines(f);
      }
      int result = fclose(f);  // try to close
      if (result != 0) {       // check if we can close
        fprintf(stderr, "File could not be closed!");
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
