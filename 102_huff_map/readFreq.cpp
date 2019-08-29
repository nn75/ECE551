#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream getInput;
  getInput.open(fname);
  if (getInput.fail()) {
    std::cout << "Open file failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * freqArray = new uint64_t[257]();
  char c;
  while ((c = getInput.get()) != EOF) {
    freqArray[(unsigned char)c]++;
  }
  freqArray[256] = 1;
  getInput.close();
  return freqArray;
}
