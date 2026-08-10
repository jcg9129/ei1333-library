#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

/**

 * @brief Maximum Independent Set(最大独立集合)
 */
template <typename Matrix>
std::vector<int> maximum_independent_set(const Matrix& g, int trial = 1000000) {
  int N = (int)g.size();
  std::vector<std::uint64_t> bit(N);
  assert(N <= 64);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i != j) {
        assert(g[i][j] == g[j][i]);
        if (g[i][j]) bit[i] |= std::uint64_t(1) << j;
      }
    }
  }

  std::vector<int> ord(N);
  std::iota(std::begin(ord), std::end(ord), 0);
  std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
  int ret = 0;
  std::uint64_t ver = 0;
  for (int i = 0; i < trial; i++) {
    std::shuffle(std::begin(ord), std::end(ord), mt);
    std::uint64_t used = 0;
    int add = 0;
    for (int j : ord) {
      if (used & bit[j]) continue;
      used |= std::uint64_t(1) << j;
      ++add;
    }
    if (ret < add) {
      ret = add;
      ver = used;
    }
  }
  std::vector<int> ans;
  for (int i = 0; i < N; i++) {
    if ((ver >> i) & 1) ans.emplace_back(i);
  }
  return ans;
}
