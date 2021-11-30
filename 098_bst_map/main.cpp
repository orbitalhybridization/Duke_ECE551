#include <string.h>

#include <iostream>

#include "bstmap.h"

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
  bst.remove(17);
  //  bst.show();
  bst.remove(-11);
  //  bst.show();
  // test equals
  BstMap<int, int> bts;
  bts = bst;
  bts.remove(1);
  //  std::cout << "here1";
  bts.add(1, 1);
  //std::cout << "here?";

  BstMap<int, int> bt(bts);
  bt.remove(8);
  std::cout << "Done with ints" << std::endl;

  BstMap<std::string, std::string> bstr;
  bstr.add("", "");
  bstr.add("s", "");
  bstr.add("a", "");
  bstr.add("u", "");
  bstr.add("11", "");
  bstr.add("--1", "");
  bstr.add("aefre", "");
  bstr.add("w", "");
  bstr.add("tt", "");
  bstr.add("q", "");
  bstr.add("i03", "");
  bstr.add("\0", "");
  bstr.add("10", "");
  bstr.show();
  bstr.remove("--1");

  BstMap<std::string, std::string> btstr;
  btstr = bstr;
  btstr.remove("");
  //  std::cout << "here1";
  btstr.add("", "");
  //std::cout << "here?";

  BstMap<std::string, std::string> bt_(btstr);
  bt_.remove("tt");
  bt_.remove("not in list");
  std::cout << "Done with strs" << std::endl;

  BstMap<const char *, const char *> bst_ch;
  bst_ch.add("q", "");
  bst_ch.add("t", "");

  BstMap<const char *, const char *> bst_ch2 = bst_ch;
  bst_ch.remove("q");

  // create a new class!
  A a;
  // create a map w/ two of em
  BstMap<A, A> bst_A;
  const A a1 = A(1);
  const A a2 = A(2);
  const A a3 = A(3);
  const A a4 = A(4);
  bst_A.add(a1, a2);
  bst_A.add(a3, a4);
  // try remove
  bst_A.remove(a1);
  // profit.
  std::cout << "Done with classtype" << std::endl;
  return 0;
}
