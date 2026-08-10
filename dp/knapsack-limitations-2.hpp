#pragma once

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "knapsack-limitations.hpp"

template <typename T>
T knapsack_limitations(const std::vector<T>& w, const std::vector<T>& m,
                       const std::vector<int>& v, const T& W) {
  const int N = (int)w.size();
  auto v_max = *std::max_element(v.begin(), v.end());
  if (v_max == 0) return 0;
  std::vector<int> ma(N);
  std::vector<T> mb(N);
  for (int i = 0; i < N; i++) {
    ma[i] = std::min<T>(m[i], v_max - 1);
    mb[i] = m[i] - ma[i];
  }
  T sum = 0;
  for (int i = 0; i < N; i++) sum += ma[i] * v[i];
  auto dp = knapsack_limitations(v, ma, w, sum, T(-1), std::less<>());
  std::vector<int> ord(N);
  std::iota(ord.begin(), ord.end(), 0);
  std::sort(ord.begin(), ord.end(),
            [&](int a, int b) { return v[a] * w[b] > v[b] * w[a]; });
  T ret = T();
  for (int i = 0; i < dp.size(); i++) {
    if (dp[i] > W || dp[i] == -1) continue;
    T rest = W - dp[i], cost = i;
    for (auto& p : ord) {
      auto get = std::min(mb[p], rest / w[p]);
      if (get <= 0) continue;
      cost += get * v[p];
      rest -= get * w[p];
    }
    ret = std::max(ret, cost);
  }
  return ret;
}
