#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    explicit Node(T in_data) : data(in_data), next(NULL), prev(NULL) {}  // constructor
  };
  Node * head;
  Node * tail;
  int numItems;

 public:
  LinkedList() : head(NULL), tail(NULL), numItems(0) {}  // default
  void addFront(const T & item) {
    Node * new_node = new Node(item);
    if (head == NULL) {
      head = new_node;
      tail = new_node;
    }
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
    numItems++;
  }

  void addBack(const T & item) {
    Node * new_node = new Node(item);
    if (tail == NULL) {
      tail = new_node;
      head = new_node;
      return;
    }
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
    numItems++;
  }

  bool remove(const T & item) {
    for (Node * curr_node = head; curr_node != NULL; curr_node = curr_node->next) {
      if (item == curr_node->data) {
        if (curr_node == head) {  // special case, delete head
          head = curr_node->next;
        }

        if (curr_node == tail) {  // special case, delete tail
          tail = curr_node->prev;
        }
        if (curr_node->prev != NULL) {
          curr_node->prev->next = curr_node->next;
        }
        if (curr_node->next != NULL) {
          curr_node->next->prev = curr_node->prev;
        }
        delete curr_node;  // finally, delete the node
        numItems--;
        return true;
      }
    }
    return false;
  }

  LinkedList(const LinkedList & rhs) {
    for (Node * curr_node = rhs.head; curr_node != NULL; curr_node = curr_node->next) {
      addBack(curr_node->data);  // deep copy
    }
    numItems = rhs.numItems;
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      Node * temp_head = new Node(rhs.head->data);
      Node * copy_node = temp_head;
      Node * prev = NULL;
      for (Node * curr_node = rhs.head; curr_node != NULL; curr_node = curr_node->next) {
        if (curr_node->next != NULL) {  // add to next if we're not at tail
          copy_node->next = new Node(curr_node->next->data);  // create new string of data
        }
        else {  // set tail if we've reached it
          tail = copy_node;
        }
        copy_node->prev = prev;
        prev = copy_node;
        copy_node = copy_node->next;
      }

      // at this point curr_node should be tail
      Node * temp_tail = new Node(rhs.tail->data);

      for (Node * next_node = head->next; next_node != NULL;
           next_node = next_node->next) {  // delete old data
        delete next_node->prev;
      }
      delete tail;

      // set new info
      numItems = rhs.numItems;
      head = temp_head;
      tail = temp_tail;
    }
    return *this;
  }

  T & operator[](int index) const {
    assert((index <= (numItems - 1)) && (index > 0));
    int i = 0;
    Node * node_of_interest = head;
    for (Node * curr_node = head; curr_node != NULL; curr_node = curr_node->next) {
      if (i == index) {
        node_of_interest = curr_node;
      }
      i++;
    }
    return node_of_interest->data;
  }

  int find(const T & item) const {
    int index = 0;
    for (Node * curr_node = head; curr_node != NULL; curr_node = curr_node->next) {
      if (curr_node->data == item) {
        return index;
      }
      index++;
    }
    return -1;
  }

  ~LinkedList() {  // destructor
    for (Node * curr_node = head; curr_node != NULL; curr_node = curr_node->next) {
      delete curr_node;
    }
  }

  int getSize() const { return numItems; }
};
#endif
