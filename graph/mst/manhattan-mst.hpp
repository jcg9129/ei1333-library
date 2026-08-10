#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <map>
#include <numeric>
#include <utility>
#include <vector>

#include "../graph-template.hpp"

/**
 * @brief Manhattan MST
 */
template <typename T>
Edges<T> manhattan_mst(std::vector<T> xs, std::vector<T> ys) {
  assert(xs.size() == ys.size());
  Edges<T> ret;
  int n = (int)xs.size();

  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);

  for (int s = 0; s < 2; s++) {
    for (int t = 0; t < 2; t++) {
      auto cmp = [&](int i, int j) -> bool {
        return xs[i] + ys[i] < xs[j] + ys[j];
      };
      std::sort(ord.begin(), ord.end(), cmp);

      std::map<T, int> idx;
      for (int i : ord) {
        for (auto it = idx.lower_bound(-ys[i]); it != idx.end();
             it = idx.erase(it)) {
          int j = it->second;
          if (xs[i] - xs[j] < ys[i] - ys[j]) break;
          ret.emplace_back(i, j,
                           std::abs(xs[i] - xs[j]) + std::abs(ys[i] - ys[j]));
        }
        idx[-ys[i]] = i;
      }
      swap(xs, ys);
    }
    for (int i = 0; i < n; i++) xs[i] *= -1;
  }
  return ret;
}
