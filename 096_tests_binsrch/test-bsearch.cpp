#include <tgmath.h>

#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class ZeroFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 0; }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class PositiveFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return (abs(arg) + 1); }
};

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
           const char * mesg) {
  // a function for running tests

  // set max_invocations
  unsigned max_invocations;

  if (high > low) {
    max_invocations = log2(high - low) + 1;
  }
  else {
    max_invocations = 1;
  }

  CountedIntFn * foo = new CountedIntFn(max_invocations, f, mesg);
  int ans = binarySearchForZero(foo, low, high);

  if (ans != expected_ans) {
    std::cout << "Answer for " << mesg << ": " << ans << "\nNot equal to expected "
              << expected_ans << "!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main() {
  SinFunction * sin = new SinFunction();
  check(sin, 0, 150000, 52359, "sin function");
  check(sin, 0, 1, 0, "basic sin");
  ZeroFunction * zero = new ZeroFunction();
  check(zero, 0, 2, 1, "zero function");
  //  check(zero, 0, 1, 1, "zero function");
  LinearFunction * linear = new LinearFunction();
  check(linear, -1, 12, 0, "linear function");
  check(linear, -10, 12, 0, "linear function with low -10, high 12");
  check(linear, 10, 12, 10, "linear function that is strictly positive");
  check(linear, 0, 0, 0, "a linear function with all 0");
  check(linear, -11, -2, -3, "a linear funciton with all negative values");
  check(linear, 10, 10, 10, "a linear function with the same positive number");
  check(linear, 12, -12, 12, "low > high");
  //  check(linear, 0, 1, 0, "0,1,0");
  check(zero, -1, 2, 0, "new zero");
  return EXIT_SUCCESS;
}
