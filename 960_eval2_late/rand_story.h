#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
int validateBlanks(
    char * line);  // validate blanks for a line (i.e. make sure every "_" has a buddy)

category_t * parseCategoryFromBlank(
    char * blank_index);  // parse category from blank (_cat_ -> cat)

catarray_t * getCategoriesFromLine(
    char * line);  // parse line and extract categories from each blank

char * replaceBlanksWithCategory(
    char * line,
    catarray_t *
        cats);  // go through a line of words and replace each category blank with a word

char * parseLine(
    char *
        line);  // parse the udnerscores of a line and return a new line with replaced words

#endif
