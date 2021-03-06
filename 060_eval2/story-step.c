#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int validateBlanks(char * line) {
  // validate blanks for a line. i.e. make sure that every "_" has a buddy
  int currently_validated = 1;
  for (size_t i = 0; i < strlen(line); i++) {
    if ((line[i] == '_') &&
        (currently_validated)) {  // new left '_', not currently validated
      currently_validated = 0;
    }

    else if ((line[i] == '_') && (!currently_validated)) {  // right '_' validates left
      currently_validated = 1;
    }
  }
  return currently_validated;
}

category_t * parseCategory(char * blank_index) {
  // parse category from blank (_cat_ -> cat)
  char * name = malloc(sizeof(*name));            // allocate space without the _s
  for (int i = 0; blank_index[i] != '_'; i++) {   // go until we find the next '_'
    name[i] = blank_index[i];                     // copy byte into container
    name = realloc(name, sizeof(*name) * i + 1);  // reallocate size for more
  }
  name[strlen(name)] = '\0';  // add null terminator
  category_t * category = malloc(sizeof(*category));
  category->name = name;  // set name of category
  category->words = NULL;
  return category;
}

catarray_t * getCategoriesFromLine(char * line) {
  // parse line and extract categories from each blank
  catarray_t * categories = malloc(sizeof(*categories));
  category_t * array = malloc(sizeof(*array));
  size_t j = 0;  // size counter for categories
  while (*line != '\0') {
    if (*line == '_') {  // if we're at a category, add to categories
      category_t * current_category = parseCategory(line);  // _bird_ -> category_t "bird"
      array[j] = *(current_category);
      array = realloc(array, sizeof(*array) * (j + 1));
      j++;

      // we also want to skip ahead in line to after the next '_'
      line = index(line + 1, '_');
    }
    else {  // otherwise just keep going
      line++;
    }
  }
  categories->arr = array;  // set fields
  categories->n = j;
  return categories;
}

char * replaceBlanksWithWords(char * line) {
  // go through an array of words and replace each category blank with a word
  char * new_line = malloc(sizeof(*new_line));
  size_t i = 0;
  while (line != '\0') {
    if (*line == '_') {  // if we're at a category, then parse it
      category_t * category = parseCategory(line);
      const char * replacement_word = chooseWord(category->name, NULL);
      for (size_t j = 0; j < strlen(replacement_word); j++) {
        new_line[i] = replacement_word[j];  // copy new word into new line
        new_line = realloc(new_line, sizeof(*new_line) * (i + 1));
        i++;
      }
      line = index(line + 1, '_');  // skip to next '_'
    }
    else {
      new_line[i] = line[i];  // otherwise copy as normal
      new_line = realloc(new_line, sizeof(*new_line) * (i + 1));
      i++;
    }
    line++;  // increment line pointer
  }
  // add null-terminator
  new_line[i] = '\0';
  return new_line;
}

char * parseLine(char * line) {
  // Parse the underscores of a line and return a new line with replaced words
  char * parsedLine = NULL;
  // validate blanks
  if (!validateBlanks(line)) {
    fprintf(stderr, "Invalid input file! Some underscores do not have buddies!");
    exit(EXIT_FAILURE);
  }

  // replace blanks with words in their category
  parsedLine = replaceBlanksWithWords(&line[0]);

  return parsedLine;
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

  // close file
  fclose(f);
}
