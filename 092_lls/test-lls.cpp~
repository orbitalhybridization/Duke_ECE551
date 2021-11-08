#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(7);
    assert(il.head->data == 7);
    assert(il.tail->data == 7);

    // check next and previous
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    // add again
    il.addFront(6);
    assert(il.head->data == 6);
    assert(il.head->next->data == 7);        // check pushed back correctly
    assert(il.head->next->prev == il.head);  // check prev set correctly
    assert(il.head->next->next == NULL);     // check next next null
    assert(il.head->prev == NULL);           // check prev still null

    // add negative
    il.addFront(-17);
    assert(il.head->data == -17);

    // check tail
    assert(il.tail->data == 7);
  }
  void testAddBack() {
    IntList il;
    il.addBack(7);

    // check head and tail
    assert(il.tail->data == 7);
    assert(il.head->data == 7);

    // check next and previous
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    // add again
    il.addBack(6);
    assert(il.tail->data == 6);        // check tail
    assert(il.head->data == 7);        // check head
    assert(il.head->next->data == 6);  // check next
    assert(il.tail->prev->data == 7);  // check prev
    assert(il.head->next->prev == il.head);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
  }

  void testCopy() {
    IntList il;  // try to copy
    il.addBack(7);
    il.addBack(8);
    IntList nil(il);

    for (int i = 0; i < il.getSize(); i++) {
      assert(il[i] == nil[i]);
    }
    assert(nil.head->data == 7);  // check elements are the same
    assert(nil.tail->data == 8);

    assert(nil.head != NULL);  // check not null
    assert(nil.tail != NULL);

    assert(nil.getSize() == il.getSize());  // check sizes

    assert(nil.tail->prev == nil.head);  // check next and prev
    assert(nil.head->next == nil.tail);

    assert(nil.head != il.head);  // make sure deep copy
    assert(nil.tail != il.tail);

    // add to il and check
    il.addBack(3);
    assert(il.getSize() != nil.getSize());
    assert(il.tail != nil.tail);
  }

  void testAssignment() {
    IntList il;  // try to assign
    il.addBack(7);
    il.addBack(8);

    IntList nil;
    nil.addBack(8);
    nil.addBack(10010);
    nil.addBack(1010);

    nil = il;  // perform copy

    // assert
    for (int i = 0; i < il.getSize(); i++) {
      assert(il[i] == nil[i]);
    }

    // check elements
    assert(nil.head->data == 7);
    assert(nil.tail->data = 8);

    assert(nil.getSize() == il.getSize());  // check sizes

    // check copy correct
    assert(nil.tail->prev == nil.head);
    assert(nil.head->next == nil.tail);

    // assert(nil.head != il.head);
    //assert(nil.tail != il.tail);

    // check pointer correct
    //assert(nil.head == il.head);

    // add to il and check
    il.addBack(3);
    assert(il.getSize() != nil.getSize());
    assert(il.tail != nil.tail);
  }

  void testDestructor() {
    IntList * il = new IntList();
    IntList::Node * node1 = new IntList::Node(0);
    IntList::Node * node2 = new IntList::Node(0);
    il->head = node1;
    il->head->next = node2;
    delete il;
    //assert(node1 == NULL);  // make sure to delete nodes when deleting object
    //assert(node2 == NULL);
  }

  void testRemove() {
    IntList il;

    assert(!il.remove(0));  // try to remove from empty

    for (int i = 0; i < 10; i++) {  // put some nodes in
      il.addBack(i);
    }
    assert(il.remove(0));           // check a valid case (head)
    assert(il.getSize() == 9);      // make sure size changes
    assert(il.head->data == 1);     // make sure we have a new head
    assert(il.tail->data == 9);     // assert tail unchanged
    assert(il.head->prev == NULL);  //make sure head is head

    assert(il.remove(1));  // check the next valid case

    assert(il.remove(9));           // check edge valid case (tail)
    assert(il.tail->data == 8);     // check we have new tail
    assert(il.tail->next == NULL);  // check tail is tail

    assert(!il.remove(10));  // invalid case

    assert(!il.remove(0));  // check double remove case

    IntList il2;
    il2.addBack(0);  // add duplicates and check behavior
    il2.addBack(0);

    assert(il2.remove(0));
    assert(il2.getSize() == 1);
    assert(il2.remove(0));  // make sure we can remove both

    IntList il3;
    il3.addBack(1);
    il3.addBack(2);
    il3.addBack(3);
    il3.addBack(4);
    assert(il3.remove(2));
    assert(il3.head->next->data == 3);
    assert(il3.tail->prev->prev->data == 1);
    assert(il3.getSize() == 3);

    assert(il3.remove(1));
    assert(il3.head->data == 3);
    assert(il3.head->prev == NULL);
    assert(il3.tail->prev->data == 3);
    assert(il3.getSize() == 2);

    assert(il3.remove(3));
    assert(il3.head == il3.tail);
    assert(il3.head->data == 4);
    assert(il3.getSize() == 1);
    assert(il3.head->next == NULL);
    assert(il3.tail->next == NULL);
    assert(il3.head->prev == NULL);
    assert(il3.tail->prev == NULL);

    assert(il3.remove(4));
    assert(il3.head == NULL);
    assert(il3.tail == NULL);
    assert(il3.getSize() == 0);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testAssignment();
  t.testDestructor();
  t.testRemove();
  // write calls to your other test methods here

  return EXIT_SUCCESS;
}
