#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "../structure/union-find/union-find.hpp"

/**
 * @brief Offline RMQ
 **/
template <typename Comp>
std::vector<int> offline_rmq(std::vector<std::pair<int, int> >& qs,
                             const Comp& comp) {
  int n = 0;
  for (auto& [l, r] : qs) n = std::max(n, r);
  UnionFind uf(n);
  std::vector<int> st(n), mark(n), ans(qs.size());
  int top = -1;
  for (auto& [l, r] : qs) mark[r - 1]++;
  std::vector<std::vector<int> > q(n);
  for (int i = 0; i < n; i++) {
    q[i].reserve(mark[i]);
  }
  for (int i = 0; i < qs.size(); i++) {
    q[qs[i].second - 1].emplace_back(i);
  }
  for (int i = 0; i < n; i++) {
    while (~top and not comp(st[top], i)) {
      uf.unite(st[top--], i);
    }
    st[++top] = i;
    mark[uf.find(i)] = i;
    for (auto& j : q[i]) {
      ans[j] = mark[uf.find(qs[j].first)];
    }
  }
  return ans;
}
