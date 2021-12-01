#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));  // push non-zeros into priority queue
    }
  }

  while (pq.size() != 1) {
    // build tree
    Node * p1 = pq.top();  // pop first two
    pq.pop();
    Node * p2 = pq.top();
    pq.pop();

    // make a parent, sum of child freq
    Node * parent = new Node(p1, p2);
    // enqueue parent
    pq.push(parent);
  }

  // return full tree
  Node * root = pq.top();
  pq.pop();
  return root;
}
