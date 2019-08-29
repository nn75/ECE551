#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "ll.h"
#include "pair.h"
using std::vector;

template<typename K, typename V, typename Hasher>
class HashMap
{
 private:
  Hasher hash;
  vector<LinkedList<Pair<K, V> > > * table;
  size_t size;
  LinkedList<Pair<K, V> > * getList(const K & k);

 public:
}

#endif
