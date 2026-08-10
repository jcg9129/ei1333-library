#pragma once

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

#include "../graph/graph-template.hpp"
#include "../graph/tree/offline-lca.hpp"

/**
 * @brief Mo Tree(木上のMo)
 **/
template <typename T = int>
struct MoTree : Graph<T> {
  using Graph<T>::Graph;
  using Graph<T>::g;
  std::vector<int> in, vs;
  std::vector<std::pair<int, int> > qs;

 public:
  void add(int l, int r) { /* [l, r) */ qs.emplace_back(l, r); }

 private:
  void dfs(int u, int p) {
    in[u] = (int)vs.size();
    vs.emplace_back(u);
    for (auto& v : g[u]) {
      if (v != p) {
        dfs(v, u);
        vs.emplace_back(v);
      }
    }
  }

 public:
  template <typename A, typename E, typename O>
  void build(const A& add, const E& erase, const O& out) {
    int n = (int)g.size() * 2 - 1;
    vs.reserve(n);
    in.resize(g.size());
    dfs(0, -1);
    std::vector<std::pair<int, int> > lr;
    lr.reserve(qs.size());
    auto lca = offline_lca(*this, qs);
    for (auto& [l, r] : qs) {
      lr.emplace_back(std::minmax(in[l] + 1, in[r] + 1));
    }
    int q = (int)lr.size();
    int bs = n / std::min<int>(n, std::sqrt(q));
    std::vector<int> ord(q);
    std::iota(std::begin(ord), std::end(ord), 0);
    std::sort(std::begin(ord), std::end(ord), [&](int a, int b) {
      int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
      if (ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second
                          : lr[a].second < lr[b].second;
    });
    int l = 0, r = 0;
    std::vector<int> flip(g.size());
    auto f = [&](int u) {
      flip[u] ^= 1;
      if (flip[u])
        add(u);
      else
        erase(u);
    };
    for (auto& idx : ord) {
      while (l > lr[idx].first) f(vs[--l]);
      while (r < lr[idx].second) f(vs[r++]);
      while (l < lr[idx].first) f(vs[l++]);
      while (r > lr[idx].second) f(vs[--r]);
      f(lca[idx]);
      out(idx);
      f(lca[idx]);
    }
  }
};
#pragma once
