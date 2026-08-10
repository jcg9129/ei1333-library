#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

std::vector<std::int64_t> divisor(std::int64_t n) {
  std::vector<std::int64_t> ret;
  for (std::int64_t i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      ret.push_back(i);
      if (i * i != n) ret.push_back(n / i);
    }
  }
  std::sort(ret.begin(), ret.end());
  return ret;
}
