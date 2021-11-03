#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

category_t * parseCategoryFromBlank(char * blank_index) {
  // parse category from blank (_cat_ -> cat)
  blank_index++;  // skip past first '_' and look for the next
  char * name = malloc(sizeof(*name));
  for (int i = 0; *blank_index != '_'; i++) {  //copy until we find the next '_'
    name[i] = *blank_index;
    name = realloc(name, sizeof(*name) * (i + 2));
    blank_index++;
    name[i + 1] = '\0';
  }
  //  name[strlen(name)] = '\0';  // add null terminator
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
      category_t * current_category =
          parseCategoryFromBlank(&line[0]);  // _bird_ -> category_t "bird"
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

char * replaceBlanksWithCategory(char * line, catarray_t * cats) {
  // go through an line of words and replace each category blank with a word
  char * new_line = malloc(sizeof(*new_line));
  size_t i = 0;
  while (*line != '\0') {
    if (*line == '_') {  // if we're at a category, then parse it
      category_t * category = parseCategoryFromBlank(&line[0]);
      const char * replacement_word = chooseWord(category->name, cats);
      for (size_t j = 0; j < strlen(replacement_word); j++) {
        new_line = realloc(new_line, sizeof(*new_line) * (i + 1));
        new_line[i] = replacement_word[j];  // copy new word into new line
        i++;
      }
      free(category->name);
      free(category);
      line = index(line + 1, '_');  // skip to next '_'
    }
    else {
      new_line = realloc(new_line, sizeof(*new_line) * (i + 1));
      new_line[i] = *line;  // otherwise copy as normal
      i++;
    }
    line++;  // increment line pointer
  }
  // add null-terminator
  new_line = realloc(new_line, sizeof(*new_line) * (i + 1));
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
  parsedLine = replaceBlanksWithCategory(&line[0], NULL);

  return parsedLine;
}
