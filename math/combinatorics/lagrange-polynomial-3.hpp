#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

/**
 * @brief Lagrange Polynomial(多項式補間, 値)
 */
template <typename Mint, typename F>
std::vector<Mint> lagrange_polynomial(const std::vector<Mint>& y,
                                      std::int64_t T, const int& m,
                                      const F& multiply) {
  int k = (int)y.size() - 1;
  T %= Mint::mod();
  if (T <= k) {
    std::vector<Mint> ret(m);
    int ptr = 0;
    for (std::int64_t i = T; i <= k and ptr < m; i++) {
      ret[ptr++] = y[i];
    }
    if (k + 1 < T + m) {
      auto suf = lagrange_polynomial(y, k + 1, m - ptr, multiply);
      for (int i = k + 1; i < T + m; i++) {
        ret[ptr++] = suf[i - (k + 1)];
      }
    }
    return ret;
  }
  if (T + m > Mint::mod()) {
    auto pref = lagrange_polynomial(y, T, Mint::mod() - T, multiply);
    auto suf = lagrange_polynomial(y, 0, m - pref.size(), multiply);
    std::copy(std::begin(suf), std::end(suf), std::back_inserter(pref));
    return pref;
  }

  std::vector<Mint> finv(k + 1, 1), d(k + 1);
  for (int i = 2; i <= k; i++) finv[k] *= i;
  finv[k] = Mint(1) / finv[k];
  for (int i = k; i >= 1; i--) finv[i - 1] = finv[i] * i;
  for (int i = 0; i <= k; i++) {
    d[i] = finv[i] * finv[k - i] * y[i];
    if ((k - i) & 1) d[i] = -d[i];
  }

  std::vector<Mint> h(m + k);
  for (int i = 0; i < m + k; i++) {
    h[i] = Mint(1) / (T - k + i);
  }

  auto dh = multiply(d, h);

  std::vector<Mint> ret(m);
  Mint cur = T;
  for (int i = 1; i <= k; i++) cur *= T - i;
  for (int i = 0; i < m; i++) {
    ret[i] = cur * dh[k + i];
    cur *= T + i + 1;
    cur *= h[i];
  }
  return ret;
}
