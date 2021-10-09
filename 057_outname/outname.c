#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  char * outputName;
  size_t fullsize = sizeof(*inputName) * strlen(inputName) +
                    8 * (sizeof(outputName));  // calculate fullsize of output

  outputName = malloc(fullsize);
  outputName = strcpy(outputName, inputName);
  char * nullIndex = strchr(outputName, '\0');  // overwrite the original null terminator
  char * suffix = ".counts";  // this syntax should auto add a null terminator
  strcpy(nullIndex, suffix);
  return outputName;
}
