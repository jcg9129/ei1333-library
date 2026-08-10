#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <stack>
#include <utility>
#include <vector>

#include "../graph-template.hpp"
#include "./centroid.hpp"

/**
 * @brief Tree-Isomorphism(木の同型性判定)
 */
template <typename T>
bool tree_isomorphism(const Graph<T>& a, const Graph<T>& b) {
  if (a.size() != b.size()) return false;

  const int N = (int)a.size();
  using pvi = std::pair<std::vector<int>, std::vector<int> >;

  auto get_uku = [&](const Graph<T>& t, int e) {
    std::stack<std::pair<int, int> > st;
    st.emplace(e, -1);
    std::vector<int> dep(N, -1), par(N);
    while (!st.empty()) {
      auto p = st.top();
      if (dep[p.first] == -1) {
        dep[p.first] = p.second == -1 ? 0 : dep[p.second] + 1;
        for (auto& to : t[p.first])
          if (to != p.second) st.emplace(to, p.first);
      } else {
        par[p.first] = p.second;
        st.pop();
      }
    }
    return std::make_pair(dep, par);
  };

  auto solve = [&](const pvi& latte, const pvi& malta) {
    int d = *std::max_element(std::begin(latte.first), std::end(latte.first));
    if (d != *std::max_element(std::begin(malta.first), std::end(malta.first)))
      return false;

    std::vector<std::vector<int> > latte_d(d + 1), malta_d(d + 1), latte_key(N),
        malta_key(N);

    for (int i = 0; i < N; i++) latte_d[latte.first[i]].emplace_back(i);
    for (int i = 0; i < N; i++) malta_d[malta.first[i]].emplace_back(i);

    for (int i = d; i >= 0; i--) {
      std::map<std::vector<int>, int> ord;
      for (auto& idx : latte_d[i]) {
        std::sort(std::begin(latte_key[idx]), std::end(latte_key[idx]));
        ord[latte_key[idx]]++;
      }
      for (auto& idx : malta_d[i]) {
        std::sort(std::begin(malta_key[idx]), std::end(malta_key[idx]));
        if (--ord[malta_key[idx]] < 0) return false;
      }
      if (i == 0) return ord.size() == 1;

      int ptr = 0;
      for (auto& p : ord) {
        if (p.second != 0) return false;
        p.second = ptr++;
      }
      for (auto& idx : latte_d[i]) {
        latte_key[latte.second[idx]].emplace_back(ord[latte_key[idx]]);
      }
      for (auto& idx : malta_d[i]) {
        malta_key[malta.second[idx]].emplace_back(ord[malta_key[idx]]);
      }
    }
    assert(0);
  };
  auto p = centroid(a), q = centroid(b);
  if (p.size() != q.size()) return false;
  auto a1 = get_uku(a, p[0]);
  auto b1 = get_uku(b, q[0]);
  if (solve(a1, b1)) return true;
  if (p.size() == 1) return false;
  auto a2 = get_uku(a, p[1]);
  return solve(a2, b1);
}
