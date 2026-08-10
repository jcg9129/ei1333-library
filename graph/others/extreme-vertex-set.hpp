#pragma once

#include <cassert>
#include <functional>
#include <iterator>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

#include "../graph-template.hpp"

template <typename T>
Graph<T> extreme_vertex_set(int n, const Edges<T>& es) {
  for (auto& e : es) {
    assert(0 <= e.from and e.from < n);
    assert(0 <= e.to and e.to < n);
    assert(e.from != e.to);
    assert(0 <= e.cost);
  }
  using pi = std::pair<int, T>;
  Graph<T> res(2 * n - 1);
  std::vector<int> uf(n);
  std::vector<T> cur(2 * n - 1);
  std::iota(uf.begin(), uf.end(), 0);
  std::vector<bool> leaf(2 * n - 1);
  for (int i = 0; i < n; i++) {
    leaf[i] = true;
  }
  using qi = std::pair<T, int>;
  std::priority_queue<qi, std::vector<qi>, std::greater<> > que;
  for (int phase = 0; phase < n - 1; phase++) {
    Graph<T> g(2 * n - 1);
    std::vector<T> cost(2 * n - 1);
    for (auto e : es) {
      e.from = uf[e.from];
      e.to = uf[e.to];
      if (e.from != e.to) {
        cost[e.from] += e.cost;
        cost[e.to] += e.cost;
        g.add_edge(e.from, e.to, e.cost);
      }
    }
    for (int i = 0; i < 2 * n - 1; i++) {
      if (leaf[i]) {
        cur[i] = cost[i];
        que.emplace(cost[i], i);
      }
    }
    int x = -1, y = -1;
    while (not que.empty()) {
      auto [c, v] = que.top();
      que.pop();
      if (cur[v] == -1) {
        continue;
      }
      cur[v] = -1;
      y = x;
      x = v;
      for (auto& e : g[v]) {
        if (cur[e.to] != -1) {
          cur[e.to] -= e.cost;
          que.emplace(cur[e.to], e.to);
        }
      }
    }
    int z = n + phase;
    res.add_directed_edge(z, x, cost[x]);
    res.add_directed_edge(z, y, cost[y]);
    for (int i = 0; i < n; i++) {
      if (uf[i] == x or uf[i] == y) {
        uf[i] = z;
      }
    }
    leaf[x] = false;
    leaf[y] = false;
    leaf[z] = true;
  }
  return res;
}
#pragma once
