#include <stdexcept>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

    Node() : key(0), value(0), left(NULL), right(NULL){};
    Node(K key_, V value_) : key(key_), value(value_), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  virtual void add(const K & key, const V & value) { root = add(root, key, value); }

  Node * add(Node * current, const K & key, const V & value) {  // helper function
    if (current == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }
    else {
      if (key < current->key) {
        Node * newLeft = add(current->left, key, value);
        current->left = newLeft;
      }
      else {
        Node * newRight = add(current->right, key, value);
        current->right = newRight;
      }
      return current;
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("not right");
  }

  virtual void remove(const K & key) {
    // go left once then all the way right
    Node * to_delete = root;
    Node * prev = NULL;
    // find thing to remove
    // keep track of parent or

    while (to_delete != NULL) {
      prev = to_delete;
      if (to_delete->key == key) {
        break;
      }
      else if (key < to_delete->key) {
        to_delete = to_delete->left;
      }
      else {
        to_delete = to_delete->right;
      }
    }
    // one right child case and no child case
    if (to_delete->left == NULL) {
      Node * temp = to_delete->right;
      if (to_delete == prev->right) {
        delete to_delete;
        prev->right = temp;
      }
      else {
        delete to_delete;
        prev->left = temp;
      }
    }
    else if (to_delete->right == NULL) {  // one left child case
      Node * temp = to_delete->left;
      if (to_delete == prev->right) {
        delete to_delete;
        prev->right = temp;
      }
      else {
        delete to_delete;
        prev->left = temp;
      }
    }
    else {  // two-child case
      std::pair<K, V> kv = helperRemove(to_delete);
      to_delete->key = kv.first;
      to_delete->value = kv.second;
    }
  }

  std::pair<K, V> helperRemove(Node * node) {
    Node * current = node->left;  // left one then right a bunch
    Node * prev = NULL;
    while (current->right != NULL) {
      prev = current;
      current = current->right;
    }
    std::pair<K, V> ret = std::make_pair(current->key, current->value);
    if (current->left != NULL) {
      current->left = prev->left;
    }
    delete current;
  }

  void clear(Node * node) {  // do a postorder traversal
    if (node != NULL) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }
  virtual ~BstMap<K, V>() { clear(root); }
};
