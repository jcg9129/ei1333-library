#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>

template <typename T>
struct BinaryBasis {
  std::vector<T> basis;
  bool update;

  BinaryBasis() : update(false) {}

  bool add(T bit) {
    for (auto& p : basis) {
      bit = std::min(bit, bit ^ p);
    }
    if (bit) {
      basis.emplace_back(bit);
      return update = true;
    } else {
      return false;
    }
  }

  bool check(T bit) const {
    for (auto& p : basis) {
      bit = std::min(bit, bit ^ p);
    }
    return bit == 0;
  }

  void normalize() {
    sweep();
    for (int i = (int)basis.size() - 1; i >= 0; i--) {
      for (int j = i - 1; j >= 0; j--)
        basis[i] = std::min(basis[i], basis[i] ^ basis[j]);
    }
  }

  void sweep() {
    if (std::exchange(update, false)) {
      std::sort(std::begin(basis), std::end(basis));
    }
  }

  bool operator==(BinaryBasis<T>& a) {
    normalize(), a.normalize();
    return basis == a.basis;
  }

  T get_kth(std::int64_t k) { /* 0-indexed */
    if ((1LL << basis.size()) <= k) {
      return -1;
    }
    T ret = T();
    sweep();
    for (int i = (int)basis.size() - 1; i >= 0; i--) {
      if (k < (1LL << i)) {
        ret = std::min(ret, ret ^ basis[i]);
      } else {
        k -= 1LL << i;
        ret = std::max(ret, ret ^ basis[i]);
      }
    }
    return ret;
  }

  std::size_t size() const { return basis.size(); }
};
