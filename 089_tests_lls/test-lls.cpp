#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.h"

int main(void) {
  IntList L1;
  assert(L1.getSize() == 0);
  
  L1.addFront(1);//1
  assert(L1[0] == 1);
  assert(L1.getSize() == 1);

  L1.addFront(2);//L1:2-1
  assert(L1[0] == 2);
  assert(L1[1] == 1);
  assert(L1.getSize() == 2);
  
  L1.addFront(3);//L1:3-2-1
  assert(L1[0] == 3);
  assert(L1[1] == 2);
  assert(L1[2] == 1);
  assert(L1.getSize() == 3);

  L1.addFront(4);//L1:4-3-2-1
  assert(L1[0] == 4);
  assert(L1[1] == 3);
  assert(L1[2] == 2);
  assert(L1[3] == 1);
  assert(L1.getSize() == 4);
  
  L1.addBack(5);//L1:4-3-2-1-5
  assert(L1[0] == 4);
  assert(L1[1] == 3);
  assert(L1[2] == 2);
  assert(L1[3] == 1);
  assert(L1[4] == 5);
  assert(L1.getSize() == 5);

  IntList L2(L1);//L2:4-3-2-1-5
  assert(L2[0] == 4);
  assert(L2[1] == 3);
  assert(L2[2] == 2);
  assert(L2[3] == 1);
  assert(L2[4] == 5);
  assert(L2.find(4) == 0);
  assert(L2.find(3) == 1);
  assert(L2.find(2) == 2);
  assert(L2.find(1) == 3);
  assert(L2.find(5) == 4);
  assert(L2.getSize() == 5);

  L1[0] = 6;//L1:6-3-2-1-5
  assert(L2[0] == 4);
  assert(L2.find(4) == 0);
  
  assert(L2.remove(4));//L2:3-2-1-5
  assert(L2[0] == 3);
  assert(L2[1] == 2);
  assert(L2[2] == 1);
  assert(L2[3] == 5);
  assert(L2.find(4) == -1);
  assert(L2.find(3) == 0);
  assert(L2.find(2) == 1);
  assert(L2.find(1) == 2);
  assert(L2.find(5) == 3);
  assert(L2.getSize() == 4);
  
  L2.remove(1);//3-2-5
  assert(L2[0] == 3);
  assert(L2[1] == 2);
  assert(L2[2] == 5);
  assert(L2.find(4) == -1);
  assert(L2.find(3) == 0);
  assert(L2.find(2) == 1);
  assert(L2.find(1) == -1);
  assert(L2.find(5) == 2);
  assert(L2.getSize() == 3);
  
  L2.remove(5);//3-2
  assert(L2[0] == 3);
  assert(L2[1] == 2);
  assert(L2.find(4) == -1);
  assert(L2.find(3) == 0);
  assert(L2.find(2) == 1);
  assert(L2.find(1) == -1);
  assert(L2.find(5) == -1);
  assert(L2.getSize() == 2);
  
  //copy L4(empty) to L3(not empty)
  IntList L3(L1);
  IntList L4;
  L3 = L4;
  assert(L3.getSize() == 0);
  
  

  return EXIT_SUCCESS;
}
