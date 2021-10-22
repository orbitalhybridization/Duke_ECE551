#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];  // init elements
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] data;  // delete original data
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {  // fill new field with elements of rhs
      temp[i] = rhs.data[i];
    }
    numElements = rhs.numElements;
    data = temp;  // set new array
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  assert(index >= 0);
  int & ret = data[index];
  return ret;
}
int & IntArray::operator[](int index) {
  assert(index < numElements);
  assert(index >= 0);
  int & ret = data[index];
  return ret;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }

  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {  // check each index has same element
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return true;
  }

  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return true;
    }
  }
  return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
  }
  else {
    s << "{";
    for (int i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1] << "}";
  }
  return s;
}
