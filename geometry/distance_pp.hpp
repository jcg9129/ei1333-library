#pragma once

#include <cmath>

#include "point.hpp"

namespace geometry {
Real distance(const Point& a, const Point& b) { return std::abs(a - b); }
}  // namespace geometry
