#pragma once

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#include "base.hpp"

namespace geometry {
using Point = std::complex<Real>;

std::istream& operator>>(std::istream& is, Point& p) {
  Real a, b;
  is >> a >> b;
  p = Point(a, b);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  return os << std::real(p) << " " << std::imag(p);
}

Point operator*(const Point& p, const Real& d) {
  return Point(std::real(p) * d, std::imag(p) * d);
}

// rotate point p counterclockwise by theta rad
Point rotate(Real theta, const Point& p) {
  return Point(std::cos(theta) * std::real(p) - std::sin(theta) * std::imag(p),
               std::sin(theta) * std::real(p) + std::cos(theta) * std::imag(p));
}

Real cross(const Point& a, const Point& b) {
  return std::real(a) * std::imag(b) - std::imag(a) * std::real(b);
}

Real dot(const Point& a, const Point& b) {
  return std::real(a) * std::real(b) + std::imag(a) * std::imag(b);
}

bool compare_x(const Point& a, const Point& b) {
  return equals(std::real(a), std::real(b)) ? std::imag(a) < std::imag(b)
                                            : std::real(a) < std::real(b);
}

bool compare_y(const Point& a, const Point& b) {
  return equals(std::imag(a), std::imag(b)) ? std::real(a) < std::real(b)
                                            : std::imag(a) < std::imag(b);
}

using Points = std::vector<Point>;
}  // namespace geometry
