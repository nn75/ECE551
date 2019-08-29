#include "point.h"

#include <stdlib.h>

#include <cmath>

Point::Point() : x(0), y(0) {}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double x1 = p.x-x;
  double y1 = p.y-y;
  return sqrt(x1 * x1 + y1 * y1);
}
