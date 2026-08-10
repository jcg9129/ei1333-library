#pragma once

#include <algorithm>
#include <vector>

#include "prime-table.hpp"

std::vector<int> enumerate_primes(int n) {
  if (n <= 1) return {};
  auto d = prime_table(n);
  std::vector<int> primes;
  primes.reserve(std::count(d.begin(), d.end(), true));
  for (int i = 0; i < d.size(); i++) {
    if (d[i]) primes.push_back(i);
  }
  return primes;
}
