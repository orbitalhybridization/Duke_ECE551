#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //  int point = low + ((high - low) / 2);  // set point to midpoint
  //  int f_x = f->invoke(point);            // run the function

  // while (((point != low) || (point != high - 1))) {
  while (high > (low + 1)) {
    int point = low + ((high - low) / 2);
    int f_x = f->invoke(point);
    //  while ((high - 1) != low) {
    //  while (true) {
    std::cout << "High : " << high << std::endl;
    std::cout << "Low : " << low << std::endl;
    std::cout << "Point: " << point << std::endl;
    if (f_x == 0) {
      return point;
    }
    else if (f_x < 0) {  // check if it's better
      low = point;
      //binarySearchForZero(f, point, high);
    }

    else {
      high = point;
      //        binarySearchForZero(f, low, point);
    }
  }
  return low;
}
