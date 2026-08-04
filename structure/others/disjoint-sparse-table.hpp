#pragma once

#include <algorithm>
#include <vector>

/**
 * @brief Disjoint-Sparse-Table
 *
 */
template <typename Semigroup, typename F>
struct DisjointSparseTable {
  const F f;
  std::vector<std::vector<Semigroup>> st;
  std::vector<int> lookup;

  DisjointSparseTable(const std::vector<Semigroup>& v, const F& f) : f(f) {
    const int n = (int)v.size();
    int b = 0;
    while ((1 << b) <= n) ++b;
    st.resize(b, std::vector<Semigroup>(n, Semigroup()));
    for (int i = 0; i < n; i++) st[0][i] = v[i];
    for (int i = 1; i < b; i++) {
      int shift = 1 << i;
      for (int j = 0; j < n; j += shift << 1) {
        int t = std::min(j + shift, n);
        st[i][t - 1] = v[t - 1];
        for (int k = t - 2; k >= j; k--) st[i][k] = f(v[k], st[i][k + 1]);
        if (n <= t) break;
        st[i][t] = v[t];
        int r = std::min(t + shift, n);
        for (int k = t + 1; k < r; k++) st[i][k] = f(st[i][k - 1], v[k]);
      }
    }
    lookup.resize(1 << b);
    for (int i = 2; i < (1 << b); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  Semigroup fold(int l, int r) {
    if (l >= --r) return st[0][l];
    int p = lookup[l ^ r];
    return f(st[p][l], st[p][r]);
  }
};

template <typename SemiGroup, typename F>
DisjointSparseTable<SemiGroup, F> get_disjoint_sparse_table(
    const std::vector<SemiGroup>& v, const F& f) {
  return {v, f};
}
