#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"
#include "set.h"

int main(void) {
  BstSet<int> set;

  set.add(60);
  set.add(19);
  set.add(93);
  set.add(4);
  set.add(25);
  set.add(84);
  set.add(1);
  set.add(11);
  set.add(21);
  set.add(35);
  set.add(70);
  set.add(86);

  //std::cout << "Lookup key is: " << set.contains(1) << std::endl;
  //std::cout << "Lookup key is: " << set.contains(86) << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  set.printInorder(set.getRoot());

  set.remove(60);
  //set.remove(93);
  //set.remove(19);
  //set.remove(60);

  set.printInorder(set.getRoot());

  //std::cout << "Lookup key is:"  <<set.contains(6) << std::endl;

  return EXIT_SUCCESS;
}
