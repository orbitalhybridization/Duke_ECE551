/* write your class interface in this file
   write function definitions only if they are very short
 */

class Vector2D {
 private:
  double x;
  double y;
  Vector2D() : x(0), y(0) {}  // default constructor
 public:
  Vector2D(double initx, double inity) : x(initx), y(inity) {}
  double getMagnitude() const;  // get sqrt(x^2 + y^2) from cmath

  Vector2D operator+(const Vector2D & rhs) const;  // vector addition in usual way

  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const;

  void print() const;  // print <%.2f,%.2f>
};
