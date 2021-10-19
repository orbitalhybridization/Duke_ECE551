#include "circle.hpp"

#include <stdlib.h>

#include <cmath>

void Circle::move(double dx, double dy) {
  // move center of circle
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  // calculate the intersection area between this circle and other
  double r_sq = std::pow(otherCircle.radius, 2);
  double R_sq = std::pow(this->radius, 2);
  double r = otherCircle.radius;
  double R = this->radius;
  double d = this->center.distanceFrom(otherCircle.center);
  double d_sq = std::pow(d, 2);
  double area =
      r_sq * std::acos((d_sq + r_sq - R_sq) / 2 * d * r) +
      R_sq * std::acos((d_sq - r_sq + R_sq) / 2 * d * R) -
      0.5 * std::pow((d + r - R) * (d - r + R) * (-d + r + R) * (d + r + R), 0.5);
  return area;
};
