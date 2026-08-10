#pragma once

#include <cmath>

#include "base.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "point.hpp"
#include "projection.hpp"

namespace geometry {
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
Points cross_point_cl(const Circle& c, const Line& l) {
  Point pr = projection(l, c.p);
  if (equals(std::abs(pr - c.p), c.r)) return {pr};
  Point e = (l.b - l.a) / std::abs(l.b - l.a);
  auto k = std::sqrt(std::norm(c.r) - std::norm(pr - c.p));
  return {pr - e * k, pr + e * k};
}
}  // namespace geometry
