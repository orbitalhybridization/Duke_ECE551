#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fillBuffer(char * buffer,
                char * src,
                char * stop_point) {  // fill a buffer up to a stop poin source
  size_t i = 0;
  while (src != stop_point) {
    buffer = realloc(
        buffer, (i + 1) * sizeof(*buffer));  // reallocate buffer as we add stuff to it
    buffer[i] = *src;                        // add new element
    src++;
    i++;
  }
}

kvpair_t * parseKVPair(char * line) {       // parse a key value pair from a line
  kvpair_t * kv = malloc(sizeof(*kv));      // init return pair in heap
  char * equals_index = strchr(line, '=');  // find first occurrence of '='
  fillBuffer(kv->key, line, equals_index);  // fill key field with key

  // at this point we should be at the first '=' so skip and do the same for value
  line++;

  fillBuffer(kv->value, line, NULL);  // copy whatever's left into value field

  return kv;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {  // check if file able to be opened
    fprintf(stderr, "This file was unable to be opened");
    exit(EXIT_FAILURE);
  }

  kvarray_t * all_kvs = malloc(sizeof(*all_kvs));   // allocate for return struct
  kvpair_t * kv_array = malloc(sizeof(*kv_array));  // allocate for array of kvs

  size_t i = 0;

  // read from file, dynamically allocating kvarray
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {   // read lines from file until we hit the end
    kvpair_t * pair = parseKVPair(line);  // parse kv pair (Make sure to free the fields!)
    kv_array = realloc(kv_array, sizeof(*kv_array) * (i + 1));  // reallocate size
    kv_array[i] = *pair;  // new element of array point to parsed pair
    i++;                  // add to total size
    free(line);           // reset buffer
  }
  free(line);  // free bit of memory allocated at last call when while loop breaks
  all_kvs->size = malloc(sizeof(*all_kvs->size));  // allocate size field
  *(all_kvs->size) = i;                            // fill field
  all_kvs->array = kv_array;                       // fill field

  return all_kvs;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < *(pairs->size); i++) {  // go through each kv_pair
    kvpair_t pair = pairs->array[i];             // free malloc'd fields of struct
    free(pair.key);
    free(pair.value);
    free(&pairs->array[i]);  // free struct itself
  }

  free(pairs->size);  // free fields of kv array struct
  free(pairs->array);

  free(pairs);  // free struct itself
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < *(pairs->size); i++) {  // loop through all pairs
    kvpair_t pair = pairs->array[i];
    printf("key = '%s' value = '%s'\n", pair.key, pair.value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < *(pairs->size); i++) {
    kvpair_t pair = pairs->array[i];   // loop through for key
    if (strcmp(pair.key, key) == 0) {  // compare for equality
      return pair.value;
    }
  }

  return NULL;
}
