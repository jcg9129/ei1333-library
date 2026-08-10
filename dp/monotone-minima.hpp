#pragma once

#include <functional>
#include <utility>
#include <vector>

template <typename T, typename Compare = std::less<T> >
std::vector<std::pair<int, T> > monotone_minima(
    int H, int W, const std::function<T(int, int)>& f,
    const Compare& comp = Compare()) {
  std::vector<std::pair<int, T> > dp(H);
  std::function<void(int, int, int, int)> dfs = [&](int top, int bottom,
                                                    int left, int right) {
    if (top > bottom) return;
    int line = (top + bottom) / 2;
    T ma;
    int mi = -1;
    for (int i = left; i <= right; i++) {
      T cst = f(line, i);
      if (mi == -1 || comp(cst, ma)) {
        ma = cst;
        mi = i;
      }
    }
    dp[line] = std::make_pair(mi, ma);
    dfs(top, line - 1, left, mi);
    dfs(line + 1, bottom, mi, right);
  };
  dfs(0, H - 1, 0, W - 1);
  return dp;
}
