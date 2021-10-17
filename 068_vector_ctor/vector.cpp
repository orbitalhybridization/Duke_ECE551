#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

double Vector2D::getMagnitude() const {
  return std::sqrt(std::pow((this->x), 2) + std::pow((this->y), 2));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D newVector;
  newVector.initVector(this->x + rhs.x, this->y + rhs.y);
  return newVector;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return ((this->x * rhs.x) + (this->y * rhs.y));
}

void Vector2D::print() const {
  printf("<%.2f,%.2f>", this->x, this->y);
}
