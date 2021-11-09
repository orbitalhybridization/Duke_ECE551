#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void processStoryTemplate(char * filename,
                          catarray_t * categories,
                          int no_reuse);  // open story template and read line by line

catarray_t * parseCategoryFile(
    char * filename);  // open and read a file of categories line by line

int validateBlanks(
    char * line);  // validate blanks for a line (i.e. make sure every "_" has a buddy)

category_t * parseCategoryFromBlank(
    char * blank_index);  // parse category from blank (_cat_ -> cat)

//catarray_t * getCategoriesFromLine(
//  char * line);  // parse line and extract categories from each blank

char * replaceBlanksWithCategory(
    char * line,
    catarray_t * cats,
    category_t * previous_cats,
    int no_reuse);  // go through a line of words and replace each category blank with a word

char * parseStoryLine(
    char * line,
    catarray_t * categories,
    category_t * previous_categories,
    int no_reuse);  // parse the udnerscores of a line and return a new line with replaced words

category_t parseCategoryLine(
    char * line);  // parse line of words into a category_t (formate = "category:word")

int categoryIndex(
    char * name,
    category_t * arr,
    size_t
        n_categories);  // check if a category is in categories. if so, return its index. if not, return -1

void addWordToCategory(const char * word,
                       category_t * category);  //add word to a category

category_t * addNewCategory(category_t category,
                            category_t * arr,
                            size_t n_categories);  // add new category to an array

const char * chooseFromPrevious(
    size_t number,
    category_t * previous);  // choose a word from list of previously used ones

int checkForIntCategory(char * name);  // check if a category name is a valid integer

char * removeWordFromCategory(char * category_name,
                              const char * word,
                              catarray_t * categories);
// remove word from category so it cannot be reused

void freeCategory(category_t * category);  // free individual category

void freeCatArray(catarray_t * categories);  // free fields of a catarray struct

/*
*/
#endif
