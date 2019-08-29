#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int>
{
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

class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class SimpleFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int remaining = 0;
  if (low == high) {
    remaining = 1;
  }
  else if (low > high) {
    remaining = 1;
  }
  else {
    remaining = log2(high - low) + 1;
  }
  CountedIntFn * cif = new CountedIntFn(remaining, f, mesg);
  int result = binarySearchForZero(cif, low, high);
  if (result != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  //SinFunction * sf = new SinFunction();
  //check(sf, 0, 150000, 52359, "Sin\n");
  SimpleFunction * smf = new SimpleFunction();
  check(smf, 1, 1, 1, "Positive Empty\n");
  check(smf, 0, 2, 0, "Zero,no negative\n");
  check(smf, -1, 1, 0, "Zero,negative\n");
  check(smf, -4, -2, -3, "Negative\n");
  check(smf, -1, -1, -1, "Negative Empty\n");
  check(smf, -2, 0, -1, "No Positive\n");
  check(smf, 1, 2, 1, "All positive");
  check(smf, -2, 4, 0, "big log");
}
