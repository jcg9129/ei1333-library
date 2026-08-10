#pragma once

#include <cstdint>
#include <vector>

#include "enumeration.hpp"

/**
 * @brief Lagrange Polynomial(多項式補間, 値)
 */
template <typename T>
T lagrange_polynomial(const std::vector<T>& y, std::int64_t t) {
  int N = y.size() - 1;
  Enumeration<T> comb(N);
  if (t <= N) return y[t];
  T ret(0);
  std::vector<T> dp(N + 1, 1), pd(N + 1, 1);
  for (int i = 0; i < N; i++) dp[i + 1] = dp[i] * (t - i);
  for (int i = N; i > 0; i--) pd[i - 1] = pd[i] * (t - i);
  for (int i = 0; i <= N; i++) {
    T tmp = y[i] * dp[i] * pd[i] * comb.finv(i) * comb.finv(N - i);
    if ((N - i) & 1)
      ret -= tmp;
    else
      ret += tmp;
  }
  return ret;
}
