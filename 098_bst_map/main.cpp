#include <string.h>

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

  return 0;
}
