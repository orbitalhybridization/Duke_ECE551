#include <iostream>
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

    explicit Node() : key(0), value(0), left(NULL), right(NULL){};
    Node(K key_, V value_) : key(key_), value(value_), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstMap() : root(NULL){};

  BstMap(const BstMap & rhs) : root(NULL) { setEqual(this, rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    this->clear(this->root);
    setEqual(this, rhs.root);
    return *this;
  }

  void setEqual(BstMap * new_tree, Node * node) {
    if (node != NULL) {
      new_tree->add(node->key, node->value);
      setEqual(new_tree, node->left);
      setEqual(new_tree, node->right);
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
    throw std::invalid_argument("requested value not found");
  }
  virtual void add(const K & key, const V & value) {
    Node * current = root;
    Node * prev = NULL;
    if (root == NULL) {
      root = new Node(key, value);
      return;
    }
    while (current != NULL) {  // get to the end
      prev = current;
      if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    if (key < prev->key) {
      prev->left = new Node(key, value);
    }
    else {
      prev->right = new Node(key, value);
    }
  }
  virtual void remove(const K & key) {
    // go left once then all the way right
    Node * to_delete = root;
    Node * prev = root;
    // find thing to remove
    // keep track of parent or

    while (to_delete != NULL) {
      if (to_delete->key == key) {
        break;
      }
      else if (key < to_delete->key) {
        prev = to_delete;
        to_delete = to_delete->left;
      }
      else {
        prev = to_delete;
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
    Node * prev_ = node;
    while (current->right != NULL) {
      prev_ = current;
      current = current->right;
    }
    std::pair<K, V> ret = std::make_pair(current->key, current->value);
    if (current->left != NULL) {
      prev_->right = current->left;
    }
    else {
      prev_->left = NULL;
    }
    delete current;
    return ret;
  }
  /*
  void go() { traverse(root); }
  void traverse(Node * node) {
    if (node != NULL) {
      traverse(node->left);
      traverse(node->right);
      std::cout << "Encountered: " << node->key << std::endl;
    }
  }
  */

  void clear(Node * node) {  // do a postorder traversal
    if (node != NULL) {
      clear(node->left);
      clear(node->right);
      //std::cout << "Deleteing: " << node->key << std::endl;
      delete node;
    }
  }
  virtual ~BstMap<K, V>() { clear(root); }
};
