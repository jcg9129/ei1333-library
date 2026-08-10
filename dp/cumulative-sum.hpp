#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

template <class T>
struct CumulativeSum {
  std::vector<T> data;

  CumulativeSum() = default;

  explicit CumulativeSum(std::size_t sz) : data(sz + 1, 0) {}

  void add(int k, const T& x) { data[k + 1] += x; }

  void build() {
    for (int i = 1; i < data.size(); i++) {
      data[i] += data[i - 1];
    }
  }

  T fold(int r) const {
    if (r < 0) return 0;
    return data[std::min(r, (int)data.size() - 1)];
  }

  T fold(int l, int r) const { return fold(r) - fold(l); }
};
