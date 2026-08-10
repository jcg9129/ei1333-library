#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

#include "../structure/others/binary-indexed-tree.hpp"

template <typename T>
struct StaticRangeCountDistinct {
 private:
  using BIT = BinaryIndexedTree<int>;
  std::size_t m;
  std::vector<int> xs;
  std::vector<std::vector<int> > mp;
  std::vector<std::pair<int, int> > qs;

 public:
  explicit StaticRangeCountDistinct(const std::vector<T>& vs) : xs(vs.size()) {
    std::vector<T> ys = vs;
    std::sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    m = ys.size();
    for (int i = 0; i < vs.size(); i++) {
      int p = lower_bound(ys.begin(), ys.end(), vs[i]) - ys.begin();
      xs[i] = p;
    }
  }

  void add_query(int l, int r) {
    assert(0 <= l and l <= r and r <= xs.size());
    qs.emplace_back(l, r - 1);
  }

  std::vector<std::size_t> calclate_queries() const {
    int n = (int)xs.size();
    int q = (int)qs.size();
    std::vector<std::vector<int> > ev(n);
    for (int i = 0; i < q; i++) {
      if (qs[i].first <= qs[i].second) {
        ev[qs[i].second].emplace_back(i);
      }
    }
    std::vector<int> pre(m, -1);
    BIT bit(n);
    std::vector<std::size_t> ans(q);
    for (int i = 0; i < n; i++) {
      int v = xs[i];
      if (~pre[v]) bit.apply(n - pre[v] - 1, -1);
      pre[v] = i;
      bit.apply(n - i - 1, 1);
      for (auto& j : ev[i]) {
        ans[j] = bit.prod(n - qs[j].first);
      }
    }
    return ans;
  }
};
#pragma once
