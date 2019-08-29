#include "circle.h"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

#include "point.h"
//#define PI acos(-1.0)

Circle::Circle(Point c, double r) : center(c), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double dist = center.distanceFrom(otherCircle.center);
  double r1 = this->radius;
  double r2 = otherCircle.radius;

  if (dist >= r1 + r2) {
    return 0.0;
  }
  else if (r1 >= dist + r2) {
    return M_PI * r2 * r2;
  }
  else if (r2 >= dist + r1) {
    return M_PI * r1 * r1;
  }
  else {
    double A1 = acos((r1 * r1 + dist * dist - r2 * r2) / (2 * r1 * dist));
    double sectorArea1 = r1 * r1 * A1;
    double triangleArea1 = 0.5 * r1 * r1 * sin(2 * A1);
    double intersectArea1 = sectorArea1 - triangleArea1;
    double A2 = acos((r2 * r2 + dist * dist - r1 * r1) / (2 * r2 * dist));
    double sectorArea2 = r2 * r2 * A2;
    double triangleArea2 = 0.5 * r2 * r2 * sin(2 * A2);
    double intersectArea2 = sectorArea2 - triangleArea2;
    double intersectArea = intersectArea1 + intersectArea2;
    return intersectArea;
  }
}
