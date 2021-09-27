#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  uint64_t population;
  country_t ans;
  country_t failure;
  failure.name[0] = '\0';
  failure.population = 0;

  // FILL NAME
  for (int i = 0; i < 64; i++) {
    if ((*line) == ',') {
      break;
    }  // stop if we've reached population

    else if (line == NULL) {  // check we haven't reached end of line
      fprintf(stderr, "Not a valid line.");
      return failure;
    }

    else {  // otherwise fill up name box
      ans.name[i] = *line;
    }
    line++;  // point to next character
  }

  if (*line != ',') {  // if we've gone through 64 chars but no ',' then name is too long
    fprintf(stderr, "Name too long!");
    return failure;
  }

  // FILL POPULATION
  line++;                                     // skip the comma
  const char * population_str = line;         // create container for population
  int population_int = atoi(population_str);  // convert to int
  if (population_int < 0) {                   // check for non-zero
    fprintf(stderr, "Population must be non-zero.");
    return failure;
  }

  else if (population_int > (pow(2, 64) - 1)) {  // check for size
    fprintf(stderr, "Population too large.");
    return failure;
  }

  else {
    population = (uint64_t)population_int;  // cast to proper type
    ans.population = population;
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
