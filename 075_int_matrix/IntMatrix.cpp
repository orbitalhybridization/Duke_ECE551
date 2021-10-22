#include "IntMatrix.h"

IntMatrix ::IntMatrix() : numRows(0), numColumns(0), rows(new IntArray *[0]) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  // deep copy
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[rhs.numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
    *rows[i] = *rhs.rows[i];
  }
}
IntMatrix::~IntMatrix() {
  //delete[] rows;
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  // deeop copy
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];

    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(numColumns);
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
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  assert(index >= 0);
  const IntArray & ret = *rows[index];
  return ret;
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows);
  assert(index >= 0);
  IntArray & ret = *rows[index];
  return ret;
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  IntMatrix result(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*result.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }
  return result;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[]";
  }
  else {
    s << "[";
    for (int i = 0; i < rhs.getRows() - 1; i++) {
      s << rhs[i] << ",\n";
    }
    s << rhs[rhs.getRows() - 1] << "]";
  }
  return s;
}
