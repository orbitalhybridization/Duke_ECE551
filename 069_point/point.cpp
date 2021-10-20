#include "point.hpp"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow((this->x - p.x), 2) + std::pow((this->y - p.y), 2));
}
