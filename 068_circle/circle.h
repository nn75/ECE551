//#ifndef __CODE_H__
//#define __CODE_H__
#include "point.h"

class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point c, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

//#endif
