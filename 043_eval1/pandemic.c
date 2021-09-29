#include "pandemic.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  country_t ans;

  // FILL NAME
  for (int i = 0; i < 64; i++) {
    if ((*line) == ',') {
      ans.name[i] = '\0';  // end as string
      break;
    }  // stop if we've reached population

    else if ((*line) == '\0') {  // check we haven't reached end of line
      fprintf(stderr, "Not a valid line.");
      exit(EXIT_FAILURE);
    }

    else {  // otherwise fill up name box
      ans.name[i] = *line;
    }

    line++;  // point to next character
  }

  if ((*line) !=
      ',') {  // if we've gone through 64 chars but no ',' then name is too long
    fprintf(stderr, "Name too long!");
    exit(EXIT_FAILURE);
  }

  if ((*line) == '\0') {  // check if we've reached the end
    fprintf(stderr, "No comma!");
    exit(EXIT_FAILURE);
  }

  // FILL POPULATION
  line++;                                          // skip the comma
  const char * population_str = line;              // create container for population
  uint64_t population_int = atoi(population_str);  // convert to int
  ans.population = population_int;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  int left = 0;  // set up indices for averaging
  int right = 7;
  int len_avg = n_days - 6;            // set up length of average array
  for (int i = 0; i < len_avg; i++) {  // do this number of times to fill avg
    avg[i] = 0.0;
    for (int j = left; j < right; j++) {
      avg[i] += (double)data[j];  // add to average
    }
    avg[i] = avg[i] / 7;  // average over 7 day streak
    left++;
    right++;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  double pop_ratio = (double)pop / 100000.00;  // calculate how much we need to divide by
  for (size_t i = 0; i < n_days; i++) {        // loop through data and add to double cum
    cum[i] = ((double)data[i]) / pop_ratio;
  }

  double cumulative = 0.0;
  for (size_t i = 0; i < n_days; i++) {  // loop back through and calculate cumulative
    cumulative += cum[i];
    cum[i] = cumulative;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  char * max_country_name;  // container for country with most cases
  unsigned max_number_cases = 0;
  int tie = 0;                                // boolean for whether there is a tie or not
  for (size_t i = 0; i < n_countries; i++) {  // loop through countries
    for (size_t j = 0; j < n_days; j++) {     // loop through days
      if (data[i][j] > max_number_cases) {
        tie = 0;  // if strictly greater than, then there is no tie
        max_country_name = countries[i].name;
        max_number_cases = data[i][j];
      }

      else if (data[i][j] == max_number_cases) {  // case: tie
        tie = 1;
      }
    }
  }

  if (tie) {  // if we ended with a tie, then tell the user
    printf("There is a tie between at least two countries");
  }

  else {  // otherwise print the country with the most cases
    printf("%s has the most daily cases with %u\n", max_country_name, max_number_cases);
  }
}
