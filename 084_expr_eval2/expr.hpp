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

class Operation : public Expression {
 protected:
  Expression * left_op;
  Expression * right_op;
  std::string str_rep;  // string representation of particular operation (e.g. "+")
 public:
  Operation(std::string op_type, Expression * lhs, Expression * rhs) :
      left_op(lhs),
      right_op(rhs),
      str_rep(op_type) {}

 protected:
  virtual std::string toString() const {
    std::stringstream out;  // container
    out << "(";
    out << left_op->toString();
    out << " " << str_rep << " ";
    out << right_op->toString();
    out << ")";
    return out.str();  // cast to string and return
  }

  virtual ~Operation() {
    delete left_op;
    delete right_op;
  }
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

class PlusExpression : public Operation {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : Operation("+", lhs, rhs){};
};

class MinusExpression : public Operation {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : Operation("-", lhs, rhs){};
};

class TimesExpression : public Operation {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : Operation("*", lhs, rhs){};
};

class DivExpression : public Operation {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : Operation("/", lhs, rhs){};
};
