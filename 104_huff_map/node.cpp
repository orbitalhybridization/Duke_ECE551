#include "node.h"

#include <cassert>
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    left->buildMap(b.plusZero(), theMap);  // recurse left
    right->buildMap(b.plusOne(), theMap);  // recurse right
  }
  else {  // leaf node
    //    assert((left == NULL) && (right == NULL));

    theMap.insert(
        std::pair<unsigned, BitString>(sym, b));  // insert path and symbol into map
  }
}
