#pragma once

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

#include "../graph-template.hpp"

template <typename T = int>
struct StronglyConnectedComponents : Graph<T> {
  using Graph<T>::Graph;
  using Graph<T>::g;
  std::vector<int> comp;
  Graph<T> dag;
  std::vector<std::vector<int>> group;

  void build() {
    comp.assign(g.size(), -1);
    order.assign(g.size(), -1);
    low.resize(g.size());
    in_stack.assign(g.size(), false);
    dfs_stack.clear();
    dfs_stack.reserve(g.size());
    vertex_stack.clear();
    vertex_stack.reserve(g.size());
    int now = 0, ptr = 0;
    for (std::size_t i = 0; i < g.size(); i++) {
      if (order[i] == -1) dfs(static_cast<int>(i), now, ptr);
    }
    for (int& component : comp) component = ptr - 1 - component;

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
  std::vector<int> order, low, in_stack, vertex_stack;
  std::vector<std::pair<int, std::size_t>> dfs_stack;

  void dfs(int root, int& now, int& component_count) {
    dfs_stack.clear();
    order[root] = low[root] = now++;
    in_stack[root] = true;
    vertex_stack.push_back(root);
    dfs_stack.emplace_back(root, 0);
    while (!dfs_stack.empty()) {
      auto& [v, edge_index] = dfs_stack.back();
      if (edge_index < g[v].size()) {
        int to = g[v][edge_index++].to;
        if (order[to] == -1) {
          order[to] = low[to] = now++;
          in_stack[to] = true;
          vertex_stack.push_back(to);
          dfs_stack.emplace_back(to, 0);
        } else if (in_stack[to]) {
          low[v] = std::min(low[v], order[to]);
        }
        continue;
      }

      dfs_stack.pop_back();
      if (!dfs_stack.empty()) {
        int parent = dfs_stack.back().first;
        low[parent] = std::min(low[parent], low[v]);
      }
      if (low[v] != order[v]) continue;
      while (true) {
        int u = vertex_stack.back();
        vertex_stack.pop_back();
        in_stack[u] = false;
        comp[u] = component_count;
        if (u == v) break;
      }
      component_count++;
    }
  }
};
