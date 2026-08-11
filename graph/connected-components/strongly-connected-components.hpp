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
  std::vector<std::vector<int>> group;

  void build() {
    order.clear();
    order.reserve(g.size());
    dfs_stack.clear();
    dfs_stack.reserve(g.size());
    rdfs_stack.clear();
    rdfs_stack.reserve(g.size());
    rg = Graph<T>(g.size());
    for (std::size_t i = 0; i < g.size(); i++) {
      for (auto& e : g[i]) {
        rg.add_directed_edge(e.to, e.from, e.cost);
      }
    }
    comp.assign(g.size(), -1);
    used.assign(g.size(), 0);
    for (std::size_t i = 0; i < g.size(); i++) dfs(static_cast<int>(i));
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
    group.assign(ptr, {});
    for (std::size_t i = 0; i < g.size(); i++) {
      group[comp[i]].emplace_back(i);
    }
  }

  int operator[](int k) const { return comp[k]; }

 private:
  std::vector<int> order, used;
  std::vector<std::pair<int, std::size_t>> dfs_stack;
  std::vector<int> rdfs_stack;
  Graph<T> rg;

  void dfs(int idx) {
    if (used[idx]) return;
    used[idx] = true;
    dfs_stack.clear();
    dfs_stack.emplace_back(idx, 0);
    while (!dfs_stack.empty()) {
      auto& [v, edge_index] = dfs_stack.back();
      if (edge_index == g[v].size()) {
        order.push_back(v);
        dfs_stack.pop_back();
        continue;
      }
      int to = g[v][edge_index++].to;
      if (!used[to]) {
        used[to] = true;
        dfs_stack.emplace_back(to, 0);
      }
    }
  }

  void rdfs(int idx, int cnt) {
    if (comp[idx] != -1) return;
    comp[idx] = cnt;
    rdfs_stack.clear();
    rdfs_stack.push_back(idx);
    while (!rdfs_stack.empty()) {
      int v = rdfs_stack.back();
      rdfs_stack.pop_back();
      for (const auto& edge : rg.g[v]) {
        if (comp[edge.to] == -1) {
          comp[edge.to] = cnt;
          rdfs_stack.push_back(edge.to);
        }
      }
    }
  }
};
