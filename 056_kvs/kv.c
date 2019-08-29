#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//read the key/value pairs from a file
///free the memory for the key/value pairs
kvpair_t * getKvpairs(char * line) {
  kvpair_t * kvp = malloc(sizeof(*kvp));
  kvp->key = NULL;
  kvp->value = NULL;
  int k = 0;
  //get the key;
  while (line[k] != '=') {
    kvp->key = realloc(kvp->key, (k + 1) * sizeof(*kvp->key));
    kvp->key[k] = line[k];
    k++;
  }
  kvp->key = realloc(kvp->key, (k + 1) * sizeof(*kvp->key));
  kvp->key[k] = '\0';
  int e = 0;
  e = k + 1;
  int v = 0;
  //get the value;
  while (line[e] != '\0' && line[e] != '\n') {
    kvp->value = realloc(kvp->value, (v + 1) * sizeof(*kvp->value));
    kvp->value[v] = line[e];
    v++;
    e++;
  }
  kvp->value = realloc(kvp->value, (v + 1) * sizeof(*kvp->value));
  kvp->value[v] = '\0';
  return kvp;
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  kvarray_t * kva = malloc(sizeof(*kva));
  size_t sz = 0;
  char * line = NULL;
  int i = 0;
  kva->kvPairs = NULL;
  while (getline(&line, &sz, f) >= 0) {
    kva->kvPairs = realloc(kva->kvPairs, (i + 1) * sizeof(*kva->kvPairs));
    kva->kvPairs[i] = getKvpairs(line);
    free(line);
    line = NULL;
    i++;
  }
  free(line);
  kva->numPairs = i;
  fclose(f);
  return kva;
}
void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    free(pairs->kvPairs[i]->key);
    free(pairs->kvPairs[i]->value);
    free(pairs->kvPairs[i]);
  }
  free(pairs->kvPairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvPairs[i]->key, pairs->kvPairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->numPairs; i++) {
    if (!strcmp(pairs->kvPairs[i]->key, key)) {
      return pairs->kvPairs[i]->value;
    }
  }
  return NULL;
}
