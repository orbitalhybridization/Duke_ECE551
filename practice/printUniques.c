#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct kv_pair_ {
  char * key;
  int value;
};
typedef struct kv_pair_t kv_pair;

size_t checkSeen(char * key, kv_pair * array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (strcmp(key, array[i].key == 0)) {
      array[i].value++;
      return size;
    }

    array = realloc(sizeof(*array) * size + 1);
    size++;
    return size;
  }
}

void printUniques(kv_pair * array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (array[i].value == 1) {
      printf("%s", array[i].key);
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "NAH");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "NAH");
    exit(EXIT_FAILURE);
  }

  kv_pair * array = malloc(sizeof(*array));
  size_t array_size = 0;
  size_t sz;
  char * line;

  while (getline(&line, &sz, f) >= 0) {
    kv_pair curr_str = {line, 1};
    array[array_size] = curr_str;
    array_size = checkSeen(curr_str, array, array_size);
  }
  printUniques(array);
  fclose(f);
}
