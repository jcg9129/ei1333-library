#pragma once

#include <functional>
#include <vector>

template <typename T, typename Compare = std::greater<T> >
std::vector<T> knapsack_01(const std::vector<int>& w, const std::vector<T>& v,
                           const int& W, const T& NG,
                           const Compare& comp = Compare()) {
  const int N = (int)w.size();
  std::vector<T> dp(W + 1, NG);
  dp[0] = T();
  for (int i = 0; i < N; i++) {
    for (int j = W; j >= w[i]; j--) {
      if (dp[j - w[i]] != NG) {
        if (comp(dp[j - w[i]] + v[i], dp[j])) {
          dp[j] = dp[j - w[i]] + v[i];
        }
      }
    }
  }
  return dp;
}
