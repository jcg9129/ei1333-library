#pragma once

#include <cstddef>
#include <vector>

#include "../graph-template.hpp"
#include "incremental-bridge-connectivity.hpp"

template <typename T = int>
struct ThreeEdgeConnectedComponents : Graph<T> {
 public:
  using Graph<T>::Graph;
  using Graph<T>::g;
  std::vector<std::vector<int> > group;

  void build() {
    uf = UnionFind(g.size());
    bcc = IncrementalBridgeConnectivity(g.size());
    used.assign(g.size(), 0);
    in.assign(g.size(), 0);
    out.assign(g.size(), 0);
    deg.assign(g.size(), 0);
    low.assign(g.size(), g.size());
    for (std::size_t from = 0; from < g.size(); from++) {
      for (auto& to : g[from]) {
        if ((T)from < to) bcc.add_edge(from, to);
      }
    }
    int cnt = 0;
    for (std::size_t i = 0; i < g.size(); i++) {
      if (used[i]) continue;
      std::vector<int> tmp;
      dfs(i, -1, tmp, cnt);
      cnt++;
    }
    std::vector<int> id(g.size(), -1);
    cnt = 0;
    for (std::size_t i = 0; i < g.size(); i++) {
      if (id[uf.find(i)] == -1) id[uf.find(i)] = cnt++;
    }
    group.resize(cnt);
    for (std::size_t i = 0; i < g.size(); i++) {
      group[id[uf.find(i)]].emplace_back(i);
    }
  }

  int operator[](const int& k) { return uf.find(k); }

 private:
  std::vector<int> used;
  std::vector<int> in, out, low, deg;
  IncrementalBridgeConnectivity bcc;
  UnionFind uf;

  void absorb(std::vector<int>& path, int v, int w = -1) {
    while (!path.empty()) {
      int x = path.back();
      if (w != -1 && (in[x] > in[w] or in[w] >= out[x])) break;
      path.pop_back();
      uf.unite(v, x);
      deg[v] += deg[x] - 2;
    }
  }

  void dfs(int idx, int p, std::vector<int>& path, int& k) {
    used[idx] = 1;
    in[idx] = low[idx] = k++;
    for (auto& to : g[idx]) {
      if (idx == to || bcc.find(idx) != bcc.find(to)) continue;
      deg[idx]++;
      if (to == p) {
        p = -1;
        continue;
      }
      if (used[to]) {
        if (in[idx] > in[to]) {
          if (in[to] < low[idx]) {
            low[idx] = in[to];
            absorb(path, idx);
          }
        } else {
          deg[idx] -= 2;
          absorb(path, idx, to);
        }
      } else {
        std::vector<int> ps;
        dfs(to, idx, ps, k);
        if (deg[to] == 2) ps.pop_back();
        if (low[to] < low[idx]) {
          low[idx] = low[to];
          absorb(path, idx);
          path = ps;
        } else {
          absorb(ps, idx);
        }
      }
    }
    out[idx] = k;
    path.push_back(idx);
  }
};
