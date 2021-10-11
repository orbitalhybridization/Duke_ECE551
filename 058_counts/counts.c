#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  size_t * size = malloc(sizeof(*size));  // init fields
  *size = 0;
  one_count_t ** array = malloc(sizeof(*array));
  counts->size = size;
  counts->counts_array = array;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  // check if we've seen this name before
  for (unsigned i = 0; i < *(c->size); i++) {
    if (name == NULL) {
      char * temp = "<unknown>";  // replace null with this name
      if (strcmp(c->counts_array[i]->pattern, temp) == 0) {
        (*(c->counts_array[i]->count))++;
        return;
      }
    }
    else if (strcmp(c->counts_array[i]->pattern, name) == 0) {
      (*(c->counts_array[i]->count))++;
      return;
    }
  }

  // if we haven't seen it add it to the list and make count 1

  c->counts_array =
      realloc(c->counts_array,
              (*(c->size) + 1) * sizeof(*c->counts_array));  // reallocate to one size up
  one_count_t * newCount = malloc(sizeof(*newCount));
  char * pattern = malloc(sizeof(*pattern));

  if (name == NULL) {
    pattern = realloc(pattern, strlen("<unknown>") + 1);
    char * temp = "<unknown>";  // we want this name if null
    for (unsigned i = 0; i < strlen("<unknown>"); i++) {
      pattern[i] = temp[i];

      if (i == strlen("<unknown>") - 1) {
        pattern[i + 1] = '\0';  // add null terminator
      }
    }
    // pattern = strcpy(pattern, temp);
  }

  else {
    pattern = realloc(pattern, strlen(name) + 1);

    for (unsigned i = 0; i < strlen(name); i++) {
      pattern[i] = name[i];

      if (i == strlen(name) - 1) {
        pattern[i + 1] = '\0';  // add null terminator
      }
    }

    // pattern = strcpy(pattern, name);
  }  // this should copy to heap but check later
  unsigned * count = malloc(sizeof(*count));
  *(count) = 1;                 // init count to 1
  newCount->pattern = pattern;  // set fields
  newCount->count = count;
  c->counts_array[*(c->size)] = newCount;  // put new count in array
  (*(c->size))++;                          // increment size
}
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < *(c->size); i++) {
    one_count_t * oneCount = c->counts_array[i];  // take one from array
    fprintf(
        outFile, "%s: %u\n", oneCount->pattern, *(oneCount->count));  // and print to file
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < *(c->size); i++) {
    one_count_t * currCount = c->counts_array[i];
    free(currCount->pattern);
    free(currCount->count);
    free(currCount);  // free struct and all fields
  }
  free(c->size);
  free(c->counts_array);
  free(c);  // free struct and all fields
}
