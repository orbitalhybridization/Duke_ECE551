#include <cmath>

class Point {
 private:
  double x;
  double y;

 public:
  // default constructor
  Point() : x(0), y(0) {}

  void move(double dx, double dy);

  double distanceFrom(const Point & p);
};
