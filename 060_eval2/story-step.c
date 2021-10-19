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

char ** deconstructLine(char * line) {
  // asynchronous example from man -S 3 getaddrinfo_a
  char ** deconstructed_line = malloc(sizeof(*deconstructed_line));
  char * token;
  int i = 0;
  while ((token = strtok(line, " ")) != NULL) {
    char * current_word;
    if (token[strlen(token)] == '\n') {                  // check if we're at the new line
      current_word = strndup(token, strlen(token) - 1);  // cut off '\n' from this
    }
    else {
      current_word =
          strndup(token, strlen(token));  // otherwise copy as normal (excluding \0
    }
    deconstructed_line[i] = current_word;
    i++;
    deconstructed_line =
        realloc(deconstructed_line, sizeof(*deconstructed_line) * (i + 1));
  }
  //  deconstructed_line = realloc(deconstructed_line,sizeof(*deconstructed_line)*(i+1)); // realloc to include \n at the end
  deconstructed_line[i] = strdup("\n");  // add \n as final element
  return deconstructed_line;
}

int isCategory(char * word) {
  // check that a word is a category (starts with "_")
  // this should be called after validation
  if (word[0] == '_') {
    return 1;
  }
  return 0;
}

char * parseCategory(char * blank) {
  // parse category from blank (_cat_ -> cat)
  char * category = malloc(strlen(blank) - 2);  // allocate space without the _s
  for (size_t i = 1; i < strlen(blank) - 1; i++) {
    category[i] = blank[i];  // copy into container
  }
  return category;
}

char ** getCategoriesFromLineArray(char ** line_array) {
  // parse array of words and extract categories from each blank
  char ** categories = malloc(sizeof(*categories));
  int i = 0;  // counter for line_array
  int j = 0;  // counter for categories
  while (strcmp(line_array[i], "\n") != 0) {
    // keep going until we've reached the last part of the array // NOTE: we might need null-terminator to us strcmp
    if (isCategory(line_array[i])) {
      categories[j] = parseCategory(line_array[i]);
      j++;
      categories = realloc(categories,
                           sizeof(*categories) * (j + 1));  // reallocate for categories
    }
    i++;
  }
  categories[j] = strdup("\n");  // end categories with a \n so we can find the end aha
  return categories;
}

void replaceBlanksWithWords(char ** categories, char ** line_array) {
  // go through an array of words and replace each category blank with a word
  int i = 0;  // counter for line_array
  int j = 0;  // counter for catergories
  while (strcmp(line_array[i], "\n") != 0) {
    if (isCategory(line_array[i])) {
      const char * new_word =
          chooseWord(categories[j], NULL);  // returns a null-terminated string
      free(line_array[i]);                  // free original memory before making new
      line_array[i] = strndup(
          new_word,
          strlen(
              new_word));  // copy all but null-terminated string so we don't have to be const anymore hehehehehe
      j++;
    }
    i++;
  }
}

/*
char * reconstructToString(char ** line_array) {
  // take a line_array and reconstruct it to a string.
  // also make sure to free all the stuff inside!
  // we'll wait to write this until I've debugged line_arrays
  
  char * ret_string = malloc(sizeof(*ret_string));
  return ret_string;
}
*/

char * parseLine(char * line) {
  // Parse the underscores of a line and return a new line with replaced words
  char * parsedLine = NULL;
  // validate blanks
  if (!validateBlanks(line)) {
    fprintf(stderr, "Invalid input file! Some underscores do not have buddies!");
    exit(EXIT_FAILURE);
  }
  // deconstruct into array
  // we want to copy the line ptr because strtok will mess with the start of the pointer
  char * line_copy = line;
  char ** line_array = deconstructLine(line_copy);

  // get categories from blanks
  char ** categories = getCategoriesFromLineArray(line_array);
  // replace blanks with words in their category
  replaceBlanksWithWords(categories, line_array);
  // reconstruct into string (optional, but useful)
  //reconstructToString(line_array);
  // now free the stuff we made
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
    parseLine(line);  // go through each line and parse the underscores
  }
  free(line);

  // close file
  fclose(f);
}
