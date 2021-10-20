#include "circle.hpp"

#include <stdint.h>
#include <stdlib.h>

#include <cmath>

void Circle::move(double dx, double dy) {
  // move center of circle
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  // calculate the intersection area between this circle and other

  // test case: no intersection

  // test case: they are the same circle

  // test case: one inside the other
  double r_sq = std::pow(otherCircle.radius, 2);
  double R_sq = std::pow(radius, 2);
  double r = otherCircle.radius;
  double R = radius;
  double d = center.distanceFrom(otherCircle.center);
  double d_sq = std::pow(d, 2);

  if (d < std::abs(R - r)) {  // test case:one inside the other
    if (r < R) {
      return M_PI * r_sq;
    }
    else {
      return M_PI * R_sq;
    }
  }
  if (r == R) {  // test case the are the same
    double area =
        2 * R_sq * std::acos(d / (2 * R)) - 0.5 * d * std::pow((4 * R_sq - d_sq), 0.5);
    return area;
  }

  if (d >= (R + r)) {  // test case: no intersection
    return 0.0;
  }

  double area =
      r_sq * std::acos((d_sq + r_sq - R_sq) / (2 * d * r)) +
      R_sq * std::acos((d_sq - r_sq + R_sq) / (2 * d * R)) -
      0.5 * std::pow((d + r - R) * (d - r + R) * (-d + r + R) * (d + r + R), 0.5);
  return area;
}
