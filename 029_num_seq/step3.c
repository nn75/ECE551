// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return (6 + (-2 - x) * (3 - y));
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow == xHi || yLow == yHi) {
    return 0;
  }
  int numEven = 0;
  for (int y = yLow; y < yHi; y++) {
    for (int x = xLow; x < xHi; x++) {
      if (seq3(x, y) % 2 == 0) {
        numEven++;
      }
    }
  }
  return numEven;
}

int main(void) {
  printf("seq3(%d,%d)=%d\n", -3, 0, seq3(-3, 0));
  printf("seq3(%d,%d)=%d\n", -9, 8, seq3(-9, 8));
  printf("seq3(%d,%d)=%d\n", 1, 1, seq3(1, 1));
  printf("seq3(%d,%d)=%d\n", 0, 2, seq3(0, 2));
  printf(
      "countEveninseq3range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));

  return EXIT_SUCCESS;
}
