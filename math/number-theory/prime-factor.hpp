#pragma once

#include <cstdint>
#include <map>

std::map<std::int64_t, int> prime_factor(std::int64_t n) {
  std::map<std::int64_t, int> ret;
  for (std::int64_t i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      ret[i]++;
      n /= i;
    }
  }
  if (n != 1) ret[n] = 1;
  return ret;
}
