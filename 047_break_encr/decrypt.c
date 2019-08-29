#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void frequency(FILE * f) {
  int char_count[26] = {0};
  char c = '0';
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      char_count[c - 'a'] = char_count[c - 'a'] + 1;
    }
  }
  int max = 0;
  int max_char = 0;
  for (int i = 0; i < 26; i++) {
    if (char_count[i] > max) {
      max_char = i;
      max = char_count[i];
    }
  }
  int k = 0;
  if (max_char < 4) {
    k = 22 + max_char;
  }
  else {
    k = max_char - 4;
  }
  fprintf(stdout, "%d", k);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage:decrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  frequency(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
