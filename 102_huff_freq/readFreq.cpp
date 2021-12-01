#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * arr = new uint64_t[257]{0};
  std::ifstream f(fname);
  while (f.peek() != -1) {  // go until EoF
    int c = f.get();
    arr[c]++;
  }
  arr[256] = 1;  // set
  f.close();
  return arr;
}
