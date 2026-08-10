#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

#include "../graph-template.hpp"

template <typename T = int>
struct StronglyConnectedComponents : Graph<T> {
 public:
  using Graph<T>::Graph;
  using Graph<T>::g;
  std::vector<int> comp;
  Graph<T> dag;
  std::vector<std::vector<int> > group;

  void build() {
    rg = Graph<T>(g.size());
    for (std::size_t i = 0; i < g.size(); i++) {
      for (auto& e : g[i]) {
        rg.add_directed_edge(e.to, e.from, e.cost);
      }
    }
    comp.assign(g.size(), -1);
    used.assign(g.size(), 0);
    for (std::size_t i = 0; i < g.size(); i++) dfs(i);
    std::reverse(std::begin(order), std::end(order));
    int ptr = 0;
    for (int i : order)
      if (comp[i] == -1) rdfs(i, ptr), ptr++;
    dag = Graph<T>(ptr);
    for (std::size_t i = 0; i < g.size(); i++) {
      for (auto& e : g[i]) {
        int x = comp[e.from], y = comp[e.to];
        if (x == y) continue;
        dag.add_directed_edge(x, y, e.cost);
      }
    }
    group.resize(ptr);
    for (std::size_t i = 0; i < g.size(); i++) {
      group[comp[i]].emplace_back(i);
    }
  }

  int operator[](int k) const { return comp[k]; }

 private:
  std::vector<int> order, used;
  Graph<T> rg;

  void dfs(int idx) {
    if (std::exchange(used[idx], true)) return;
    for (auto& to : g[idx]) dfs(to);
    order.push_back(idx);
  }

  void rdfs(int idx, int cnt) {
    if (comp[idx] != -1) return;
    comp[idx] = cnt;
    for (auto& to : rg.g[idx]) rdfs(to, cnt);
  }
};
