#pragma once

#include <vector>

#include "point.hpp"

namespace geometry {
struct Circle {
  Point p;
  Real r{};

  Circle() = default;

  Circle(const Point& p, const Real& r) : p(p), r(r) {}
};

using Circles = std::vector<Circle>;
}  // namespace geometry
