#pragma once

#include <cmath>

#include "is_parallel.hpp"
#include "line.hpp"

namespace geometry {
bool is_intersect_ll(const Line& l, const Line& m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if (equals(std::abs(A), 0) && equals(std::abs(B), 0)) return true;
  return !is_parallel(l, m);
}
}  // namespace geometry
