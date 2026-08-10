#pragma once

#include <cstdint>
#include <numeric>
#include <unordered_map>

/**
 * @brief Mod Log(離散対数問題)
 *
 */
std::int64_t mod_log(std::int64_t a, std::int64_t b, std::int64_t p) {
  std::int64_t g = 1;

  for (std::int64_t i = p; i; i /= 2) (g *= a) %= p;
  g = std::gcd(g, p);

  std::int64_t t = 1, c = 0;
  for (; t % g; c++) {
    if (t == b) return c;
    (t *= a) %= p;
  }
  if (b % g) return -1;

  t /= g;
  b /= g;

  std::int64_t n = p / g, h = 0, gs = 1;

  for (; h * h < n; h++) (gs *= a) %= n;

  std::unordered_map<std::int64_t, std::int64_t> bs;
  for (std::int64_t s = 0, e = b; s < h; bs[e] = ++s) {
    (e *= a) %= n;
  }

  for (std::int64_t s = 0, e = t; s < n;) {
    (e *= gs) %= n;
    s += h;
    if (bs.count(e)) return c + s - bs[e];
  }
  return -1;
}
