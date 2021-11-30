#include <string.h>

#include <iostream>

#include "bstset.h"

class A {
  int x;

 public:
  A() : x(0) {}

  A & operator=(const A & rhs) {
    if (this != &rhs) {
      x = rhs.x;
    }
    return *this;
  }

  A(int x_in) : x(x_in) {}

  A(const A & rhs) { x = rhs.x; }

  bool operator<(const A & rhs) const {
    if (x < rhs.x) {
      return true;
    }
    return false;
  };

  bool operator>(const A & rhs) const {
    if (x > rhs.x) {
      return true;
    }
    return false;
  }

  bool operator==(const A & rhs) const {
    if (x == rhs.x) {
      return true;
    }
    return false;
  }

  bool operator!=(const A & rhs) const {
    if (x != rhs.x) {
      return true;
    }

    return false;
  }

  ~A() {}
};

int main(int argc, char ** argv) {
  BstSet<int> bst;
  bst.add(1);
  bst.add(2);
  bst.add(17);
  bst.add(6);
  bst.add(-11);
  bst.add(-12);
  bst.add(18);
  bst.add(-9);
  bst.add(-5);
  bst.add(-6);
  bst.add(5);
  bst.add(9);
  bst.add(8);
  bst.remove(17);
  //  bst.show();
  bst.remove(-11);
  //  bst.show();
  // test equals
  BstSet<int> bts;
  bts = bst;
  bts.remove(1);
  //  std::cout << "here1";
  bts.add(1);
  //std::cout << "here?";

  BstSet<int> bt(bts);
  bt.remove(8);
  std::cout << "Done with ints" << std::endl;

  BstSet<std::string> bstr;
  bstr.add("");
  bstr.add("s");
  bstr.add("a");
  bstr.add("u");
  bstr.add("11");
  bstr.add("--1");
  bstr.add("aefre");
  bstr.add("w");
  bstr.add("tt");
  bstr.add("q");
  bstr.add("i03");
  bstr.add("\0");
  bstr.add("10");
  bstr.show();
  bstr.remove("--1");

  BstSet<std::string> btstr;
  btstr = bstr;
  btstr.remove("");
  //  std::cout << "here1";
  btstr.add("");
  //std::cout << "here?";

  BstSet<std::string> bt_(btstr);
  bt_.remove("tt");
  bt_.remove("not in list");

  BstSet<const char *> bst_ch;
  bst_ch.add("q");
  bst_ch.add("t");

  BstSet<const char *> bst_ch2 = bst_ch;
  bst_ch.remove("q");
  std::cout << "Done with strs" << std::endl;

  // create a new class!
  A a;
  // create a map w/ two of em
  BstSet<A> bst_A;
  const A a1 = A(1);
  const A a2 = A(2);
  const A a3 = A(3);
  const A a4 = A(4);
  bst_A.add(a1);
  bst_A.add(a3);
  // try remove
  bst_A.remove(a1);
  // profit.
  std::cout << "Done with classtype" << std::endl;
  return 0;
}
