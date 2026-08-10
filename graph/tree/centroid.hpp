#pragma once

#include <algorithm>
#include <stack>
#include <utility>
#include <vector>

#include "../graph-template.hpp"

/**
 * @brief Centroid(木の重心)
 *
 */
template <typename T>
std::vector<int> centroid(const Graph<T>& g) {
  const int N = (int)g.size();

  std::stack<std::pair<int, int> > st;
  st.emplace(0, -1);
  std::vector<int> sz(N), par(N);
  while (!st.empty()) {
    auto p = st.top();
    if (sz[p.first] == 0) {
      sz[p.first] = 1;
      for (auto& to : g[p.first])
        if (to != p.second) st.emplace(to, p.first);
    } else {
      for (auto& to : g[p.first])
        if (to != p.second) sz[p.first] += sz[to];
      par[p.first] = p.second;
      st.pop();
    }
  }

  std::vector<int> ret;
  int size = N;
  for (int i = 0; i < N; i++) {
    int val = N - sz[i];
    for (auto& to : g[i])
      if (to != par[i]) val = std::max(val, sz[to]);
    if (val < size) size = val, ret.clear();
    if (val == size) ret.emplace_back(i);
  }

  return ret;
}
