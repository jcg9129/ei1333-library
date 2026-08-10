#pragma once

#include <cmath>

#include "base.hpp"
#include "line.hpp"

namespace geometry {
Point cross_point_ll(const Line& l, const Line& m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if (equals(std::abs(A), 0) && equals(std::abs(B), 0)) return m.a;
  return m.a + (m.b - m.a) * B / A;
}
}  // namespace geometry
