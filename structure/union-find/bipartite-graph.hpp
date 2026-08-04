#pragma once

#include <vector>

#include "union-find.hpp"

struct BipartiteGraph : UnionFind {
  std::vector<int> color;

  BipartiteGraph(int v) : UnionFind(v + v), color(v + v, -1) {}

  bool bipartite_graph_coloring() {
    const int n = (int)color.size() / 2;
    for (int i = 0; i < n; i++) {
      int a = find(i);
      int b = find(i + n);
      if (a == b) return (false);
      if (color[a] < 0) color[a] = 0, color[b] = 1;
    }
    return (true);
  }

  bool operator[](int k) { return (bool(color[find(k)])); }
};
