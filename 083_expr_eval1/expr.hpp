#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;  // abstract method
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long input_num) : num(input_num){};

  virtual std::string toString() const {
    std::stringstream out;  // container
    out << num;             // put num in string stream
    return out.str();       // cast to string and return
  }
};

class PlusExpression : public Expression {
 private:
  Expression * left_op;
  Expression * right_op;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left_op(lhs), right_op(rhs){};

  virtual std::string toString() const {
    std::stringstream out;  // container
    out << "(";
    out << left_op->toString();
    out << " + ";
    out << right_op->toString();
    out << ")";
    return out.str();  // cast to string and return
  }
};
