#pragma once

#include <vector>

#include "line.hpp"

namespace geometry {
struct Segment : Line {
  Segment() = default;

  using Line::Line;
};

using Segments = std::vector<Segment>;
}  // namespace geometry
