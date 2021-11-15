#include <iostream>

#include "bstmap.h"

int main(int argc, char ** argv) {
  BstMap<int, int> bst;
  bst.add(1, 1);
  bst.add(2, 1);
  bst.add(17, 1);
  bst.add(6, 1);
  bst.add(-11, 1);
  bst.add(-12, 1);
  bst.add(18, 1);
  bst.add(-9, 1);
  bst.add(-5, 1);
  bst.add(-6, 1);
  bst.add(5, 1);
  bst.add(9, 1);
  bst.add(8, 1);
  std::cout << "Removing 17" << std::endl;
  bst.remove(17);
  std::cout << "done" << std::endl;
  return 0;
}
