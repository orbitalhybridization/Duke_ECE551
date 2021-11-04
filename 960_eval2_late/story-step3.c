/*
#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

char * replaceBlanksWithCategory(char * line,
                                 catarray_t * cats,
                                 catarray_t * previous_words) {
  // go through an line of words and replace each category blank with a word
  char * new_line = malloc(sizeof(*new_line));
  size_t i = 0;
  while (*line != '\0') {
    if (*line == '_') {  // if we're at a category, then parse it
      category_t * category = parseCategoryFromBlank(&line[0]);
      if ((49 <= category->name[0]) && (category->name[0] <= 57)) {
        // check if category is a valid int of at least one
        // if so, choose a previous word
        choosePreviousWord(category->name, previous_cats);
      }
      else {  // otherwise choose a new word
        const char * replacement_word = chooseWord(category->name, cats);
      }
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

int main(int argc, char ** argv) {
  // check correct args
  if (argc != 3) {
    fprintf(stderr, "Correct usage: ./story-step3 [words file] [story template file]");
    exit(EXIT_FAILURE);
  }
}
*/
int main() {
  return 1;
}
