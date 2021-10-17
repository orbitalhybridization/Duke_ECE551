#include <cmath>

class Point {
 private:
  double x;
  double y;

 public:
  // default constructor
  Point() : x(0), y(0) {}

  void move(double dx, double dy) {
    x += dx;
    y += dy;
  }

  double distanceFrom(const Point & p) {
    return std::sqrt(std::pow((this->x - p.x), 2) + std::pow((this->y - p.y), 2));
  }
};
