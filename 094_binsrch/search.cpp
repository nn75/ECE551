#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  high = high - 1;
  if (low == high+1) {
    return low;
  }
  if (f->invoke(low) >= 0) {
    return low;
  }
  if (f->invoke(high) <= 0) {
    return high;
  }
  int search = 0;
  int mid = 0;
  while (low <= high) {
    mid = (low + high) / 2;
    search = f->invoke(mid);
    if (search == 0) {
      return mid;
    }
    else if (search < 0) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  if(mid>high){
    return mid-1;
  }
  return mid;
}
