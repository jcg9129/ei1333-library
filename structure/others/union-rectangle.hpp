#pragma once

#include <cstdint>
#include <limits>
#include <map>

template <typename T>
struct UnionRectangle {
  std::map<T, T> data;
  std::int64_t sum;

  UnionRectangle() : sum(0) {
    const T INF = std::numeric_limits<T>::max();
    data[0] = INF;
    data[INF] = 0;
  }
  void add_point(T x, T y) {
    auto p = data.lower_bound(x);
    if (p->second >= y) return;
    const T nxtY = p->second;
    --p;
    while (p->second <= y) {
      auto it = *p;
      p = --data.erase(p);
      sum -= (it.first - p->first) * (it.second - nxtY);
    }
    sum += (x - p->first) * (y - nxtY);
    data[x] = y;
  }

  std::int64_t get() { return sum; }
};
