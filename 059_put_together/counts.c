#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->keyList = NULL;
  c->numKeys = 0;
  c->numUnknown = 0;
  return c;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int exit = 0;
  if (name == NULL) {
    c->numUnknown++;
  }
  else {
    //c->keyList = malloc(sizeof(*c->keyList));
    for (int i = 0; i < c->numKeys; i++) {
      if (!strcmp(c->keyList[i]->key, name)) {
        c->keyList[i]->times++;
        exit = 1;
      }
    }
    if (exit != 1) {
      c->numKeys++;
      c->keyList = realloc(c->keyList, c->numKeys * sizeof(*c->keyList));
      c->keyList[c->numKeys - 1] = malloc(sizeof(*c->keyList[c->numKeys - 1]));
      c->keyList[c->numKeys - 1]->key = NULL;
      c->keyList[c->numKeys - 1]->times = 1;
      int j = 0;
      while (name[j] != '\0') {
        j++;
        c->keyList[c->numKeys - 1]->key =
            realloc(c->keyList[c->numKeys - 1]->key, j * sizeof(*c->keyList[c->numKeys]->key));
        c->keyList[c->numKeys - 1]->key[j - 1] = name[j - 1];
      }
      c->keyList[c->numKeys - 1]->key =
          realloc(c->keyList[c->numKeys - 1]->key, (j + 1) * sizeof(*c->keyList[c->numKeys]->key));
      c->keyList[c->numKeys - 1]->key[j] = '\0';
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->numKeys; i++) {
    fprintf(outFile, "%s: %d\n", c->keyList[i]->key, c->keyList[i]->times);
  }
  if (c->numUnknown != 0) {
    fprintf(outFile, "<unknown>: %d\n", c->numUnknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->numKeys; i++) {
    free(c->keyList[i]->key);
    // free(c->keyList[i]);
    free(c->keyList[i]);
  }
  free(c->keyList);
  free(c);
}
