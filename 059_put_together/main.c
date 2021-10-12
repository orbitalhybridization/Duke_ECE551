#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  // compute counts of values that appear in particular input file

  counts_t * counts = createCounts();
  char * line = NULL;
  size_t size;
  FILE * f = fopen(filename, "r");
  if (f == NULL) {  // error check successful open
    fprintf(stderr, "Unable to open file!");
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &size, f) >= 0) {          // get each string
    addCount(counts, lookupValue(kvPairs, line));  // add value to count if able
  }
  fclose(f);
  free(line);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)

  // check right arglength
  if (argc < 3) {
    fprintf(stderr, "Correct usage ./count_values [kvlist] ... [keylist]");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //(call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    // check we're able to open file
    if (f == NULL) {
      fprintf(stderr, "Unable to open dat file!");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    free(c);
  }
  free(kv);
  return EXIT_SUCCESS;
}
