#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
void sortLines(std::istream & in) {
  std::string line;
  std::vector<std::string> sLines;
  while (getline(in, line)) {
    sLines.push_back(line);
  }
  if (!in.eof()) {
    std::cerr << "Cannot read the file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::sort(sLines.begin(), sLines.end());

  for (std::vector<std::string>::iterator it = sLines.begin(); it != sLines.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    sortLines(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream fin(argv[i]);
      if (!fin) {
        std::cerr << "Cannot open the file" << argv[i] << std::endl;
      }
      sortLines(fin);
    }
  }
  return EXIT_SUCCESS;
}
