
#include <algorithm>
#include <vector>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 public:
  virtual void add(const T & key) {
    // add me
    data.push_back(key);
  }

  virtual bool contains(const T & key) const {
    // check me
    typename std::vector<T>::const_iterator it = std::find(data.begin(), data.end(), key);
    if (it == data.end()) {
      return true;
    }
    return false;
  }

  virtual void remove(const T & key) {
    // remove me
    typename std::vector<T>::iterator it = std::find(data.begin(), data.end(), key);
    if (it != data.end()) {
      data.erase(it);
    }
  }

  virtual ~BstSet<T>() {}

  virtual BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      for (typename std::vector<T>::const_iterator it = rhs.data.begin();
           it != rhs.data.end();
           it++) {
        data.push_back(*it);
      }
    }
    return *this;
  }

  BstSet(const BstSet & rhs) {
    for (typename std::vector<T>::const_iterator it = rhs.data.begin();
         it != rhs.data.end();
         it++) {
      data.push_back(*it);
    }
  }

  BstSet() {}
};
