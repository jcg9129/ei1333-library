#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

template <typename T>
T knapsack_01_2(const std::vector<T>& w, const std::vector<int>& v,
                const T& W) {
  const int N = (int)w.size();
  const int sum = std::accumulate(v.begin(), v.end(), 0);
  std::vector<T> dp(sum + 1, W + 1);
  dp[0] = T();
  for (int i = 0; i < N; i++) {
    for (int j = sum; j >= v[i]; j--) {
      dp[j] = std::min(dp[j], dp[j - v[i]] + w[i]);
    }
  }
  int ret = 0;
  for (int i = 0; i <= sum; i++) {
    if (dp[i] <= W) ret = i;
  }
  return ret;
}
