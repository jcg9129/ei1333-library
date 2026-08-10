#pragma once

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

#include "../graph-template.hpp"
#include "topological-sort.hpp"

/**
 * @brief Offline Dag Reachability(DAGの到達可能性クエリ)
 *
 */

template <typename T>
std::vector<int> offline_dag_reachability(
    const Graph<T>& g, std::vector<std::pair<int, int> >& qs) {
  const int N = (int)g.size();
  const int Q = (int)qs.size();
  auto ord = topological_sort(g);
  std::vector<int> ans(Q);
  for (int l = 0; l < Q; l += 64) {
    int r = std::min(Q, l + 64);
    std::vector<std::int64_t> dp(N);
    for (int k = l; k < r; k++) {
      dp[qs[k].first] |= std::int64_t(1) << (k - l);
    }
    for (auto& idx : ord) {
      for (auto& to : g[idx]) dp[to] |= dp[idx];
    }
    for (int k = l; k < r; k++) {
      ans[k] = (dp[qs[k].second] >> (k - l)) & 1;
    }
  }
  return ans;
}
