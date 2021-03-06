#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
  if (argc != 2) {  // err conditions
    fprintf(stderr, "Invalid number of args.");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {  // check for non-null return
    fprintf(stderr, "Invalid file!");
    return EXIT_FAILURE;
  }

  char non_rotated_matrix[10][10];  // init container for matrix
  int row = 0;                      // get index of matrix
  int column = 0;
  int c;  // container for char read from file
  while ((c = fgetc(f)) != EOF) {
    if (row > 9) {  // check if we've passed row max
      fprintf(stderr, "Invalid number of rows.");
      return EXIT_FAILURE;
    }

    else if (c == '\n') {  // if we've reached the end of line move to new row

      if (column != 10) {  // check if we're at 10th element tho!
        fprintf(stderr, "Invalid number of elements.");
        return EXIT_FAILURE;
      }

      else {  // otherwise increment row and reset column
        row++;
        column = 0;
      }
    }

    else {  // otherwise we're in the middle and we save numbers and treat as normal
      non_rotated_matrix[row][column] = c;
      column++;
    }
  }

  if ((row != 10) || (column != 0)) {  // check that we're really at the end
    fprintf(stderr, "Invalid matrix size.");
    return EXIT_FAILURE;
  }

  // print rotated matrix
  for (int row = 0; row < 10; row++) {  // go through matrix
    for (int column = 9; column >= 0; column--) {
      printf("%c", non_rotated_matrix[column][row]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
