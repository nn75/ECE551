#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i <= 256; i++) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node * left = NULL;
    Node * right = NULL;
    left = pq.top();
    pq.pop();
    right = pq.top();
    pq.pop();
    pq.push(new Node(left, right));
  }
  return pq.top();
}
