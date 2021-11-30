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

    Node() : key(0), value(0), left(NULL), right(NULL) {}

    Node(K in_key, V in_val) : key(in_key), value(in_val), left(NULL), right(NULL) {}

    ~Node() {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}

  BstMap & operator=(BstMap & rhs) {
    // assignment
    if (*this != rhs) {
      clear(root);          // empty all nodes
      makeEqual(rhs.root);  // do a preorder traversal to reconstruct
    }
    return *this;
  }

  BstMap(BstMap & rhs) {
    // copy ctor
    makeEqual(rhs.root);  // do a preorder traversal
  }

  void clear(Node * node) {
    // do a post order traversal
    if (node != NULL) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  void makeEqual(Node * node) {
    if (node != NULL) {
      add(node->key, node->value);
      makeEqual(node->left);
      makeEqual(node->right);
    }
  }
  /*
  Node * add_helper(Node * current, K addKey, V addValue) {
    if (current == NULL) {
      Node * ans = new Node(addKey, addValue);
      return ans;
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
    show();
    std::cout << "end show" << std::endl;
  }
  */

  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key, value);
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
    Node * parent = root;
    Node * child = root;
    if (root == NULL) {
      return;
    }
    std::cout << "Child key " << child->key << std::endl;
    while (child->key != key) {
      // find the key that we want to remove
      if (key < child->key) {
        parent = child;
        child = child->left;
      }
      else {
        parent = child;
        child = child->right;
      }
    }
    if (child == parent->left) {
      parent->left = remove_helper(child);
    }

    else {
      parent->right = remove_helper(child);
    }
    // now that we've found the one to remove,
    // we want to abort the child
  }

  Node * remove_helper(Node * node) {
    if (node->left == NULL) {
      Node * temp = node->right;
      std::cout << "Deleteing " << node->key << std::endl;
      delete node;
      return temp;
    }
    else if (node->right == NULL) {
      // has a left child
      Node * temp = node->left;
      std::cout << "Deleteing " << node->key << std::endl;
      delete node;
      return temp;
    }
    else {  // has two children
      // go left one
      Node * temp = node->left;
      // go right as much as possible
      while (temp->right != NULL) {
        temp = temp->right;
      }
      // return
      node->key = temp->key;
      node->value = temp->value;
      std::cout << "Deleteing " << temp->key << std::endl;
      delete temp;
      return node;
    }
  }

  virtual ~BstMap<K, V>() { clear(root); };

  void show() { show(root); }

  void show(Node * node) {
    if (node != NULL) {
      std::cout << "Node key : " << node->key << std::endl;
      show(node->left);
      show(node->right);
    }
  }
};
