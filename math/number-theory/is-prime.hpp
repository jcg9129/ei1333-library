#pragma once

#include <cstdint>

bool is_prime(std::int64_t x) {
  if (x < 2) return false;
  for (std::int64_t i = 2; i * i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}
