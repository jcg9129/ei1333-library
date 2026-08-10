#pragma once

#include <functional>
#include <vector>

#include "monotone-minima.hpp"

template <typename T, typename Compare = std::less<T> >
std::vector<std::vector<T> > divide_and_conquer_optimization(
    int H, int W, T INF, const std::function<T(int, int)>& f,
    const Compare& comp = Compare()) {
  std::vector<std::vector<T> > dp(H + 1, std::vector<T>(W + 1, INF));
  dp[0][0] = 0;
  for (int i = 1; i <= H; i++) {
    std::function<T(int, int)> get_cost = [&](int y, int x) {
      if (x >= y) return INF;
      return dp[i - 1][x] + f(x, y);
    };
    auto ret = monotone_minima(W + 1, W + 1, get_cost, comp);
    for (int j = 0; j <= W; j++) dp[i][j] = ret[j].second;
  }
  return dp;
}
