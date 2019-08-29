// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return (x * 4 - 3);
}

void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  for (int i = low; i < high; i++) {
    int element = i * 4 - 3;
    if (i < high - 1) {
      printf("%d, ", element);
    }
    else {
      printf("%d\n", element);
    }
  }
}

int main(void) {
  printf("seq1(%d)=%d\n", 0, seq1(0));
  printf("seq1(%d)=%d\n", 6, seq1(6));
  printf("seq1(%d)=%d\n", 10, seq1(10));
  printf("printSeq1range(%d,%d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printSeq1range(%d,%d)\n", 7, 3);
  printSeq1Range(7, 3);
  printf("printSeq1range(%d,%d)\n", 0, 0);
  printSeq1Range(0, 0);
  printf("printSeq1range(%d,%d)\n", 0, 4);
  printSeq1Range(0, 4);

  return EXIT_SUCCESS;
}
