#pragma once

#include <functional>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

#include "../../structure/others/plus-minus-one-rmq.hpp"
#include "../graph-template.hpp"

/**
 * @brief PMORMQ-Lowest-Common-Ancestor(最小共通祖先)
 *
 **/
template <typename T = int>
struct PMORMQLowestCommonAncestor : Graph<T> {
 public:
  using Graph<T>::Graph;
  using Graph<T>::g;
  using F = std::function<int(int, int)>;

  void build(int root = 0) {
    ord.reserve(g.size() * 2 - 1);
    dep.reserve(g.size() * 2 - 1);
    in.resize(g.size());
    dfs(root, -1, 0);
    std::vector<int> vs(g.size() * 2 - 1);
    std::iota(std::begin(vs), std::end(vs), 0);
    st = PlusMinusOneRMQ<int>(dep);
  }

  int lca(int x, int y) const {
    if (in[x] > in[y]) std::swap(x, y);
    return ord[st.fold(in[x], in[y] + 1).second];
  }

 private:
  std::vector<int> ord, dep, in;
  PlusMinusOneRMQ<int> st;

  void dfs(int idx, int par, int d) {
    in[idx] = (int)ord.size();
    ord.emplace_back(idx);
    dep.emplace_back(d);
    for (auto& to : g[idx]) {
      if (to != par) {
        dfs(to, idx, d + 1);
        ord.emplace_back(idx);
        dep.emplace_back(d);
      }
    }
  }
};
