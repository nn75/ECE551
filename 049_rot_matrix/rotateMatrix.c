#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void rotate(FILE * f) {
  int arr[10][10];
  int q = 0;
  int i = 0;
  int j = 0;
  while ((q = fgetc(f)) != EOF) {
    if (q != '\n') {
      arr[i][j] = q;
      //printf("%c", arr[i][j]);
      j++;
    }
    else if (q == '\n') {
      if (j != 10) {
        fprintf(stderr, "wrong row!\n");
        exit(EXIT_FAILURE);
      }
      i++;
      j = 0;
      // printf("\n");
    }
  }
  if (i != 10) {
    fprintf(stderr, "wrong line!\n");
    exit(EXIT_FAILURE);
  }

  int a = 0;
  int b = 0;
  int c = 9;
  int d = 9;
  while (a <= c && b <= d) {
    for (int x = 0; x < c - a; x++) {
      char t = arr[a + x][d];
      arr[a + x][d] = arr[a][b + x];
      arr[a][b + x] = arr[c - x][b];
      arr[c - x][b] = arr[c][d - x];
      arr[c][d - x] = t;
    }
    a++;
    b++;
    c--;
    d--;
  }

  for (int n = 0; n < 10; n++) {
    for (int m = 0; m < 10; m++) {
      fprintf(stdout, "%c", arr[n][m]);
    }
    printf("\n");
  }
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
  rotate(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
