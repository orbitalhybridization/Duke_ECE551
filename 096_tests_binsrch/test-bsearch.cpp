#include <cstdlib>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg);
// a function for running tests

// check if f called at most log2(high-low)+1 times if high>low
// otherwise at most once

//unsigned max_invocations;
// if (high>low) {
// max_invocations = log2(high-low)+1;
//}
//else {max_invocations = 1; }
// foo = CountedIntFn(max_invocations,

int main() {
  return EXIT_SUCCESS;
}
