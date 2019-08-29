#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

size_t hashCompute(std::ifstream & input) {
  std::string line;
  std::string content;
  std::hash<std::string> hashString;
  while (!input.eof()) {
    getline(input, line);
    content.append(line);
  }
  size_t hashKey = hashString(content);
  return hashKey;
}

void fileCompare(std::pair<size_t, std::string> currPair,
                 std::unordered_map<size_t, std::string> & hashTable) {
  std::unordered_map<size_t, std::string>::iterator it = hashTable.find(currPair.first);
  if (it == hashTable.end()) {
    hashTable.insert(currPair);
  }
  else {
    std::cout << "#Removing " << currPair.second << " (duplicate of " << it->second << ")."
              << std::endl;
    std::cout << "rm " << currPair.second << std::endl;
  }
}
void readDirectory(const std::string & dir, std::unordered_map<size_t, std::string> & hashTable) {
  DIR * curr;
  struct dirent * ent;
  if ((curr = opendir(dir.c_str())) == 0) {
    std::cout << "Open directory failed!" << std::endl;
    closedir(curr);
    exit(EXIT_FAILURE);
  }
  else {
    while ((ent = readdir(curr)) != NULL) {
      std::string fileName(ent->d_name);
      if (fileName.compare(".") == 0 || fileName.compare("..") == 0) {
        continue;
      }
      else {
        std::string nextDir;
        std::string file;
        std::ifstream input;
        switch (ent->d_type) {
          case DT_DIR:
            nextDir = dir + "/" + fileName;
            readDirectory(nextDir, hashTable);
            break;
          case DT_REG:
            file = dir + "/" + fileName;
            input.open(file.c_str());
            if (input.good() == 1) {
              size_t currHash;
              currHash = hashCompute(input);
              std::pair<size_t, std::string> currPair(currHash, file);
              fileCompare(currPair, hashTable);
            }
            else {
              std::cout << "Open file failed" << std::endl;
              exit(EXIT_FAILURE);
            }
            break;
          default:
            break;
        }
      }
    }
    closedir(curr);
  }
}
int main(int argc, char ** argv) {
  if (argc < 2) {
    std::cout << "Usage:./dir/file..." << std::endl;
  }
  else {
    std::unordered_map<size_t, std::string> hashTable;
    std::cout << "#!/bin/bash" << std::endl;
    int i = 1;
    while (i < argc) {
      const std::string dir = argv[i];
      readDirectory(dir, hashTable);
      i++;
    }
  }
  return EXIT_SUCCESS;
}
