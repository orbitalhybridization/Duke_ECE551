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

    Node() : key(0), value(0), left(NULL), right(NULL) {}

    Node(K in_key, V in_val) : key(in_key), value(in_val), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap & operator=(BstMap & rhs) {
    // assignment
    if (*this != rhs) {
    }
    return *this;
  }

  BstMap(BstMap & rhs) {
    // copy ctor
  }

  Node * add_helper(Node * current, K addKey, V addValue) {
    if (current == NULL) {
      Node * ans = new Node(addKey, addValue);
    }
    else {
      if (addKey < current->key) {
        Node * newLeft = add_helper(current->right, addKey, addValue);
        current->left = newLeft;
      }

      else {
        Node * newRight = add_helper(current->left, addKey, addValue);
        current->right = newRight;
      }

      return current;
    }
  }

  virtual void add(const K & key, const V & value) {
    root = add_helper(root, key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw(std::invalid_argument("Key not found"));
  }

  virtual void remove(const K & key) {
    // try to use a pointer to a pointer
    Node * to_remove = root;
    while (to_remove->key != key) {
      // find the key that we want to remove
      if (key < to_remove->key) {
        to_remove = to_remove->left;
      }
      else {
        to_remove = to_remove->right;
      }
    }

    Node ** clip = &to_remove;
    // cases:
    if (clip->left == NULL) {  // one or no children
      Node * temp = *(clip)->right;
      delete clip;
      return clip;
    }
    else if (clip->right == NULL) {  // one left child
    }

    else {  // two children
    }
  }

  virtual ~BstMap<K, V>(){};
};
