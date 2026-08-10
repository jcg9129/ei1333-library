#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

template <typename T>
std::vector<T> convert_base(T x, T b) {
  std::vector<T> ret;
  T t = 1, k = std::abs(b);
  while (x) {
    ret.emplace_back((x * t) % k);
    if (ret.back() < 0) ret.back() += k;
    x -= ret.back() * t;
    x /= k;
    t *= b / k;
  }
  if (ret.empty()) ret.emplace_back(0);
  std::reverse(ret.begin(), ret.end());
  return ret;
}
