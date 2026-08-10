#pragma once

#include <cmath>

#include "line.hpp"
#include "projection.hpp"

namespace geometry {
Real distance_lp(const Line& l, const Point& p) {
  return std::abs(p - projection(l, p));
}
}  // namespace geometry
