/* write your class interface in this file
   write function definitions only if they are very short
 */

class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double init_x, double init_y) {
    x = init_x;
    y = init_y;
  }

  double getMagnitude() const;  // get sqrt(x^2 + y^2) from cmath

  Vector2D operator+(const Vector2D & rhs) const;  // vector addition in usual way

  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const;

  void print() const;  // print <%.2f,%.2f>
};
