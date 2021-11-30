#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;

    Node(T in_data) : key(in_data), left(NULL), right(NULL) {}

    ~Node() {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}

  BstSet & operator=(const BstSet & rhs) {
    // assignment
    if (this != &rhs) {
      clear(root);  // empty all nodes
      root = NULL;
      makeEqual(rhs.root);  // do a preorder traversal to reconstruct
    }
    return *this;
  }

  BstSet(const BstSet & rhs) : root(NULL) {
    // copy ctor
    //    std::cout << "key " << rhs.root->key << std::endl;
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
      add(node->key);
      makeEqual(node->left);
      makeEqual(node->right);
    }
  }

  Node * add_helper(Node * current, const T & addData) {
    if (current == NULL) {
      Node * ans = new Node(addData);
      return ans;
    }
    else {
      if (addData < current->key) {
        Node * newLeft = add_helper(current->left, addData);
        current->left = newLeft;
      }

      else if (addData > current->key) {
        Node * newRight = add_helper(current->right, addData);
        current->right = newRight;
      }

      //else {  // same key

      //}

      return current;
    }
  }

  virtual void add(const T & key) { root = add_helper(root, key); }

  /*
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
  */

  virtual bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  virtual void remove(const T & key) {
    // keep track of parent
    Node * parent = root;
    Node * child = root;
    if (root == NULL) {
      return;
    }
    while (child != NULL) {
      if (child->key == key) {
        break;  // no key found
      }
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

    if (child == NULL) {
      return;
    }

    if (child == parent->left) {
      parent->left = remove_helper(child);
    }
    else if (child == parent->right) {
      parent->right = remove_helper(child);
    }

    else {  // root
      root = remove_helper(child);
    }
    // now that we've found the one to remove,
    // we want to abort the child
  }

  Node * remove_helper(Node * node) {
    if (node->left == NULL) {
      Node * temp = node->right;
      //      std::cout << "Deleting " << node->key << std::endl;
      delete node;
      return temp;
    }
    else if (node->right == NULL) {
      // has a left child
      Node * temp = node->left;
      //std::cout << "Deleting " << node->key << std::endl;
      delete node;
      return temp;
    }
    else {  // has two children
      // go left one
      Node * temp = node->left;
      Node * temp_parent = node;
      // go right as much as possible
      while (temp->right != NULL) {
        temp_parent = temp;
        temp = temp->right;
      }
      // return
      //      node->key = temp->key;
      //node->value = temp->value;
      if (temp == temp_parent->left) {
        temp_parent->left = temp->left;
      }
      else {
        temp_parent->right = temp->left;
      }
      Node * new_node = new Node(temp->key);
      new_node->left = node->left;
      new_node->right = node->right;

      delete temp;
      delete node;
      return new_node;
    }
  }

  virtual ~BstSet<T>() { clear(root); };

  void show() { show(root); }

  void show(Node * node) {
    if (node != NULL) {
      //      std::cout << "Node key : " << node->key << std::endl;
      show(node->left);
      show(node->right);
    }
  }
};
