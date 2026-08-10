#pragma once

#include <cmath>

#include "base.hpp"
#include "circle.hpp"
#include "point.hpp"

namespace geometry {
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
Points cross_point_cc(const Circle& c1, const Circle& c2) {
  Real d = std::abs(c1.p - c2.p), r = c1.r + c2.r;
  if (sign(d - r) > 0 or sign(d + c1.r - c2.r) < 0) return {};
  Real a = std::acos((std::norm(c1.r) - std::norm(c2.r) + std::norm(d)) /
                     (2 * c1.r * d));
  Real t = std::arg(c2.p - c1.p);
  Point p = c1.p + std::polar(c1.r, t + a);
  Point q = c1.p + std::polar(c1.r, t - a);
  if (equals(std::real(p), std::real(q)) && equals(std::imag(p), std::imag(q)))
    return {p};
  return {p, q};
}
}  // namespace geometry
