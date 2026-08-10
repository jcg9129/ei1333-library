#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

template <typename T = int>
struct Edge {
  int from, to;
  T cost;
  int idx;

  Edge() = default;

  Edge(int from, int to, T cost = 1, int idx = -1)
      : from(from), to(to), cost(cost), idx(idx) {}

  operator int() const { return to; }
};

template <typename T = int>
struct Graph {
  std::vector<std::vector<Edge<T> > > g;
  int es;

  Graph() = default;

  explicit Graph(int n) : g(n), es(0) {}

  std::size_t size() const { return g.size(); }

  void add_directed_edge(int from, int to, T cost = 1) {
    g[from].emplace_back(from, to, cost, es++);
  }

  void add_edge(int from, int to, T cost = 1) {
    g[from].emplace_back(from, to, cost, es);
    g[to].emplace_back(to, from, cost, es++);
  }

  void read(int M, int padding = -1, bool weighted = false,
            bool directed = false) {
    for (int i = 0; i < M; i++) {
      int a, b;
      std::cin >> a >> b;
      a += padding;
      b += padding;
      T c = T(1);
      if (weighted) std::cin >> c;
      if (directed)
        add_directed_edge(a, b, c);
      else
        add_edge(a, b, c);
    }
  }

  inline std::vector<Edge<T> >& operator[](const int& k) { return g[k]; }

  inline const std::vector<Edge<T> >& operator[](const int& k) const {
    return g[k];
  }
};

template <typename T = int>
using Edges = std::vector<Edge<T> >;
