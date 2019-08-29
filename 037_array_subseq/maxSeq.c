#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (array == NULL || n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  int len = 1;
  int max_len = 1;
  for (size_t i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      len = len + 1;
    }
    else {
      len = 1;
    }
    if (len > max_len) {
      max_len = len;
    }
  }
  return max_len;
}
