#include "rand_story.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processStoryTemplate(char * filename, catarray_t * categories) {
  // open story template and read line by line
  // then close
  FILE * f = fopen(filename, "r");
  // error check file opened correctly
  if (f == NULL) {
    fprintf(stderr, "Could not open file!");
    exit(EXIT_FAILURE);
  }

  size_t sz;
  char * line = NULL;
  // set up container for previous categories to pass with each read
  category_t * previous_categories = malloc(sizeof(*previous_categories));
  previous_categories->name = strdup("1");  // make default name for this container
  previous_categories->n_words = 0;
  char ** words = malloc(sizeof(*words));
  previous_categories->words = words;

  // now read line by line
  while (getline(&line, &sz, f) >= 0) {
    char * parsedLine = parseStoryLine(line, categories, previous_categories);
    printf("%s",
           parsedLine);  // go through each line and parse the underscores, and print!
    free(parsedLine);
  }
  free(line);
  freeCategory(previous_categories);
  free(previous_categories);
  freeCatArray(categories);
  fclose(f);
}

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

const char * chooseFromPrevious(size_t number, category_t * previous) {
  // choose word from previous
  if (number >
      previous->n_words) {  // check if we're being asked to go further than possible
    fprintf(stderr,
            "Cannot parse previous word specifier. Requested number larger than "
            "available words!\n");
    exit(EXIT_FAILURE);
  }
  return previous->words[previous->n_words - number];
}

int checkForIntCategory(char * name) {
  // check if a category name is a number
  // based off of code from (man strtol(3))
  // return 0 if not, otherwise return number
  char * endptr;
  long as_long = strtol(name, &endptr, 10);

  // if we don't have a number at all
  if (endptr == name) {
    return 0;
  }

  // error checking specifically for valid int
  if ((as_long <= 0) || (as_long >= ((pow(2, sizeof(int)) / 2) - 1))) {
    fprintf(stderr, "Requested nunber %ld not a valid integer.\n", as_long);
    exit(EXIT_FAILURE);
  }

  // error checking from man strtol(3)
  // check if outside of range of possible long or some other error
  errno = 0;
  if ((errno == ERANGE && (as_long == LONG_MAX || as_long == LONG_MIN)) ||
      (errno != 0 && as_long == 0)) {
    fprintf(stderr, "Requested number %ld not a valid integer.\n", as_long);
    exit(EXIT_FAILURE);
  }

  // otherwise we have a valid int, so return it as an int!
  int return_int = as_long;
  return return_int;
}
char * replaceBlanksWithCategory(char * line,
                                 catarray_t * cats,
                                 category_t * previous_cats) {
  // go through an line of words and replace each category blank with a word
  char * new_line = malloc(sizeof(*new_line));
  size_t i = 0;
  while (*line != '\0') {
    if (*line == '_') {  // if we're at a category, then parse it
      category_t * category = parseCategoryFromBlank(&line[0]);
      const char * replacement_word;  // declare replacement word for later
      int as_num =
          checkForIntCategory(category->name);  // check if we need to look in previous
      if (as_num > 0) {
        // if category is an int then choose previously used
        // cast to int
        replacement_word = chooseFromPrevious(as_num, previous_cats);
      }
      else {  // otherwise process as usual
        replacement_word = chooseWord(category->name, cats);
      }
      addWordToCategory(replacement_word, previous_cats);  // add word to previously used

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

char * parseStoryLine(char * line,
                      catarray_t * categories,
                      category_t * previous_categories) {
  // Parse the underscores of a line and return a new line with replaced words
  char * parsedLine = NULL;
  // validate blanks
  if (!validateBlanks(line)) {
    fprintf(stderr, "Invalid input file! Some underscores do not have buddies!");
    exit(EXIT_FAILURE);
  }

  // replace blanks with words in their category
  parsedLine = replaceBlanksWithCategory(&line[0], categories, previous_categories);

  return parsedLine;
}

// story step 2

catarray_t * parseCategoryFile(char * filename) {
  // open and read a file of categories line by line

  FILE * f = fopen(filename, "r");
  // error check file opened correctly
  if (f == NULL) {
    fprintf(stderr, "Could not open file!");
    exit(EXIT_FAILURE);
  }

  // set up containers
  size_t sz;
  char * line = NULL;
  catarray_t * categories = malloc(sizeof(*categories));
  category_t * arr = malloc(sizeof(*arr));
  size_t n_categories = 0;

  // read line by line
  while (getline(&line, &sz, f) >= 0) {
    category_t category = parseCategoryLine(&line[0]);
    int index = categoryIndex(category.name, arr, n_categories);
    if (index >= 0) {  // check if we've seen this category before
      addWordToCategory(category.words[0], &arr[index]);  // if so, just add its word
      freeCategory(&category);  // we're not gonna use the category we made so free it
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

  fclose(f);
  return categories;
}

category_t parseCategoryLine(char * line) {
  // parse line of words into a category_t (format = "category:word")
  category_t category;
  char * name = malloc(sizeof(*name));
  int i = 0;
  while (*line != ':') {  // fill name field with category name
    name = realloc(name, sizeof(*name) * (i + 2));
    name[i] = *line;
    line++;
    i++;
    if (*line ==
        '\0') {  // if we've reached the end without hitting a colon, then we have invalid formate
      fprintf(
          stderr,
          "Invalid category format (no colon found).  Correct format: category:word.");
      exit(EXIT_FAILURE);
    }
  }
  name[i] = '\0';  // add null terminator
  line++;
  char ** words = malloc(sizeof(*words));
  char * curr_word = malloc(sizeof(*curr_word));
  i = 0;
  while (*line != '\n') {  // fill word array with current replacement word
    curr_word = realloc(curr_word, sizeof(*curr_word) * (i + 2));
    curr_word[i] = *line;
    line++;
    i++;
  }
  curr_word[i] = '\0';  // add null terminator
  category.words = words;
  category.words[0] = curr_word;  // set array to point to copied word
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

void addWordToCategory(const char * word, category_t * category) {
  // add a word to a category
  category->words =
      realloc(category->words, sizeof(*category->words) * (category->n_words + 1));
  category->words[category->n_words] = strdup(word);
  //  strcpy(category->words[category->n_words], word);
  category->n_words++;
}

category_t * addNewCategory(category_t category, category_t * arr, size_t n_categories) {
  // add new category to an array
  arr = realloc(arr, sizeof(*arr) * (n_categories + 1));
  arr[n_categories].name = category.name;
  arr[n_categories].words = category.words;
  arr[n_categories].n_words = category.n_words;
  return arr;
}

void freeCategory(category_t * category) {
  // free individual category
  for (size_t j = 0; j < category->n_words; j++) {
    free(category->words[j]);
  }
  free(category->name);
  free(category->words);
  //free(category);
}
void freeCatArray(catarray_t * categories) {
  // free fields of a catarray struct
  for (size_t i = 0; i < categories->n; i++) {
    category_t * curr_cat = &categories->arr[i];
    freeCategory(curr_cat);
  }
  free(categories->arr);
  free(categories);
}
