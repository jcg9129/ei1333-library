#pragma once

#include <stack>
#include <vector>

/**
 * @brief Cartesian Tree
 */
template <typename T>
std::vector<int> cartesian_tree(const std::vector<T>& v) {
  int n = (int)v.size();
  std::vector<int> par(n, -1);
  std::stack<int> st;
  for (int i = 0; i < n; i++) {
    int last = -1;
    while (!st.empty() && v[st.top()] >= v[i]) {
      last = st.top();
      st.pop();
    }
    if (!st.empty()) par[i] = st.top();
    if (last >= 0) par[last] = i;
    st.emplace(i);
  }
  return par;
}
