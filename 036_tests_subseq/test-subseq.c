#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, int expected_ans) {
  if (expected_ans != maxSeq(array, n)) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int array2[] = {-1, 0, 1, 2, 3, 4, 5, 6, 7};
  int array3[] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int array4[] = {0, 0, 0, 0, 0};
  int array5[0] = {};

  run_check(array1, 8, 8);
  run_check(array2, 9, 9);
  run_check(array3, 9, 4);
  run_check(array4, 5, 1);
  run_check(array5, 0, 0);

  return EXIT_SUCCESS;
}
