#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <vector>

template <typename T>
struct Compress {
  std::vector<T> xs;

  Compress() = default;

  Compress(const std::vector<T>& vs) { add(vs); }

  Compress(const std::initializer_list<std::vector<T> >& vs) {
    for (auto& p : vs) add(p);
  }

  void add(const std::vector<T>& vs) {
    std::copy(vs.begin(), vs.end(), std::back_inserter(xs));
  }

  void add(const T& x) { xs.emplace_back(x); }

  void build() {
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  }

  std::vector<int> get(const std::vector<T>& vs) const {
    std::vector<int> ret;
    std::transform(
        vs.begin(), vs.end(), std::back_inserter(ret), [&](const T& x) {
          return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        });
    return ret;
  }

  int get(const T& x) const {
    return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  }

  const T& operator[](int k) const { return xs[k]; }
};
