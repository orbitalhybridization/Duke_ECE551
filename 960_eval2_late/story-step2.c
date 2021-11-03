#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

category_t parseWordsLine(char * line) {
  // parse line of words into a category_t (format = "category:word")
  category_t category;
  char * name = malloc(sizeof(*name));
  int i = 0;
  if (*line == ':') {  // check if we have ':' as a cat name which is illegal
    fprintf(stderr, "Can't have ':' as a category name");
    exit(EXIT_FAILURE);
  }
  while (*line != ':') {  // fill name field with category name
    name = realloc(name, sizeof(*name) * (i + 1));
    name[i] = *line;
    line++;
    i++;
  }
  line++;
  char ** words = malloc(sizeof(*words));
  char * curr_word = malloc(sizeof(*curr_word));
  i = 0;
  while (*line != '\n') {  // fill word array with current replacement word
    curr_word = realloc(curr_word, sizeof(*curr_word) * (i + 1));
    curr_word[i] = *line;
    line++;
    i++;
  }
  words[0] = curr_word;  // set array to point to copied word
  category.words = words;
  category.name = name;
  category.n_words = 1;
  return category;
}

int categoryIndex(char * name, category_t * arr, size_t n_categories) {
  // check if a category is in categories
  // if so, return its index
  // if not, return -1
  for (size_t i = 0; i < n_categories; i++) {
    if ((strcmp(name, arr[i].name) == 0)) {
      return i;
    }
  }
  return -1;
}

void addWordToCategory(char * word, category_t * arr, size_t index) {
  // add a word to a category
  arr[index].words =
      realloc(arr[index].words, sizeof(*arr[index].words) * (arr[index].n_words + 1));
  arr[index].words[arr[index].n_words] = strdup(word);
  arr[index].n_words++;
}

category_t * addNewCategory(category_t category, category_t * arr, size_t n_categories) {
  // add new category to an array
  arr = realloc(arr, sizeof(*arr) * (n_categories + 1));
  arr[n_categories].name = category.name;
  arr[n_categories].words = category.words;
  arr[n_categories].n_words = 1;
  return arr;
}

void freeCatArray(catarray_t * categories) {
  // free fields of a catarray struct
  for (size_t i = 0; i < categories->n; i++) {
    category_t * curr_cat = &categories->arr[i];
    for (size_t j = 0; j < curr_cat->n_words; j++) {
      free(curr_cat->words[j]);
    }
    free(curr_cat->words);
    free(curr_cat->name);
    //free(curr_cat);
  }
  free(categories->arr);
  free(categories);
}

catarray_t * readLines(FILE * f) {
  // read a file line by line
  size_t sz;
  char * line = NULL;
  catarray_t * categories = malloc(sizeof(*categories));
  category_t * arr = malloc(sizeof(*arr));
  size_t n_categories = 0;
  while (getline(&line, &sz, f) >= 0) {
    category_t category = parseWordsLine(&line[0]);
    int index = categoryIndex(category.name, arr, n_categories);
    if (index >= 0) {  // check if we've seen this category before
      addWordToCategory(category.words[0], arr, index);  // if so, just add its word
    }
    else {  // otherwise add as new
      arr = addNewCategory(category, arr, n_categories);
      n_categories++;
    }
  }
  free(line);

  // set fields
  categories->arr = arr;
  categories->n = n_categories;

  return categories;
}

int main(int argc, char ** argv) {
  // error check num command line args
  if (argc != 2) {
    fprintf(stderr, "Correct usage: ./story-step2 [filename]");
    exit(EXIT_FAILURE);
  }
  // open file for read
  FILE * f = fopen(argv[1], "r");
  // error check file opened correctly
  if (f == NULL) {
    fprintf(stderr, "Could not open file!");
    exit(EXIT_FAILURE);
  }

  catarray_t * categories = readLines(f);
  // print stuff
  printWords(categories);

  // free associated memory
  freeCatArray(categories);

  // close file
  fclose(f);
}
