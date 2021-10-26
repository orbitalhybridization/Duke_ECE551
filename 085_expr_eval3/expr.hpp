#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;  // abstract method
  virtual long evaluate() const = 0;         // abstract method
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 protected:
  long num;

 public:
  NumExpression(long input_num) : num(input_num){};

  virtual std::string toString() const {
    std::stringstream out;  // container
    out << num;             // put num in string stream
    return out.str();       // cast to string and return
  }

  virtual long evaluate() const { return num; }
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

  virtual long evaluate() const { return (left_op->evaluate() + right_op->evaluate()); }
  virtual ~PlusExpression() {
    delete left_op;  // free memory
    delete right_op;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * left_op;
  Expression * right_op;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : left_op(lhs), right_op(rhs){};
  virtual std::string toString() const {
    std::stringstream out;  // container
    out << "(";
    out << left_op->toString();
    out << " - ";
    out << right_op->toString();
    out << ")";
    return out.str();  // cast to string and return
  }
  virtual long evaluate() const { return (left_op->evaluate() - right_op->evaluate()); }

  virtual ~MinusExpression() {
    delete left_op;
    delete right_op;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * left_op;
  Expression * right_op;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : left_op(lhs), right_op(rhs){};
  virtual std::string toString() const {
    std::stringstream out;  // container
    out << "(";
    out << left_op->toString();
    out << " * ";
    out << right_op->toString();
    out << ")";
    return out.str();  // cast to string and return
  }

  virtual long evaluate() const { return (left_op->evaluate() * right_op->evaluate()); }

  virtual ~TimesExpression() {
    delete left_op;
    delete right_op;
  }
};

class DivExpression : public Expression {
 private:
  Expression * left_op;
  Expression * right_op;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : left_op(lhs), right_op(rhs){};

  virtual std::string toString() const {
    std::stringstream out;  // container
    out << "(";
    out << left_op->toString();
    out << " / ";
    out << right_op->toString();
    out << ")";
    return out.str();  // cast to string and return
  }
  virtual long evaluate() const { return (left_op->evaluate() / right_op->evaluate()); }
  virtual ~DivExpression() {
    delete left_op;
    delete right_op;
  }
};
