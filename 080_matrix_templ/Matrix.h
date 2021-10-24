#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(new std::vector<T> *[0]) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
    }
  }
  Matrix(const Matrix & rhs) {
    // deep copy
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new std::vector<T> *[rhs.numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
      *rows[i] = *rhs.rows[i];
    }
  }
  ~Matrix() {
    //delete[] rows;
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    // deeop copy
    if (this != &rhs) {
      std::vector<T> ** temp = new std::vector<T> *[rhs.numRows];

      for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = new std::vector<T>(numColumns);
        *temp[i] = *rhs.rows[i];
      }

      for (int i = 0; i < numRows; i++) {  // clear old fields
        delete rows[i];
      }
      delete[] rows;

      rows = temp;  // add new info
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index < numRows);
    assert(index >= 0);
    const std::vector<T> & ret = *rows[index];
    return ret;
  }
  std::vector<T> & operator[](int index) {
    assert(index < numRows);
    assert(index >= 0);
    std::vector<T> & ret = *rows[index];
    return ret;
  }

  bool operator==(const Matrix & rhs) const {
    if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
      return false;
    }

    for (int i = 0; i < numRows; i++) {
      if (*rows[i] != *rhs.rows[i]) {
        return false;
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    Matrix result(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*result.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
      }
    }
    return result;
  }
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[]";
  }
  else {
    s << "[";
    for (int i = 0; i < rhs.getRows(); i++) {  // iterate through rows
      s << "{";
      std::vector<T> row = rhs[i];
      typename std::vector<T>::iterator it = row.begin();
      while (it != row.end()) {            // do for whole row
        if (it == (row.end() - 1)) {       // end of row
          if (i == (rhs.getRows() - 1)) {  // are we on the last row?
            s << *it << "}";
          }
          else {  // if not keep goin!
            s << *it << "},\n";
          }
        }
        else {  // if we're not at end of row we want commas
          s << *it << ", ";
        }
        ++it;  // increment iterator
      }
    }

    s << "]";
  }
  return s;
}

#endif
