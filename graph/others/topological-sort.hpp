#pragma once

#include <stack>
#include <vector>

#include "../graph-template.hpp"

/**
 * @brief Topological Sort(トポロジカルソート)
 *
 */
template <typename T>
std::vector<int> topological_sort(const Graph<T>& g) {
  const int N = (int)g.size();
  std::vector<int> deg(N);
  for (int i = 0; i < N; i++) {
    for (auto& to : g[i]) ++deg[to];
  }
  std::stack<int> st;
  for (int i = 0; i < N; i++) {
    if (deg[i] == 0) st.emplace(i);
  }
  std::vector<int> ord;
  while (!st.empty()) {
    auto p = st.top();
    st.pop();
    ord.emplace_back(p);
    for (auto& to : g[p]) {
      if (--deg[to] == 0) st.emplace(to);
    }
  }
  return ord;
}
