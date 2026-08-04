#pragma once

#include <cstddef>
#include <utility>
#include <vector>

/**
 * @brief Linear-RMQ
 **/
template <typename Comp>
struct LinearRMQ {
  std::vector<int> small;
  std::vector<std::vector<int>> large;

  LinearRMQ() = default;

  Comp comp;

  static inline int msb(int c) { return 31 - __builtin_clz(c); }

  static inline int ctz(unsigned int c) { return __builtin_ctz(c); }

  inline int get_min(int l, int r) const { return comp(l, r) ? l : r; }

  explicit LinearRMQ(std::size_t size, const Comp& comp) : comp(comp) {
    const int n = (int)size;
    std::vector<int> st;
    st.reserve(32);
    large.emplace_back();
    large.front().reserve(n / 32);
    small.reserve(n);
    for (int i = 0; i < n; i++) {
      while (!st.empty() && !comp(st.back(), i)) {
        st.pop_back();
      }
      small.emplace_back(st.empty() ? 0 : small[st.back()]);
      small.back() |= 1U << (i % 32);
      st.emplace_back(i);
      if ((i + 1) % 32 == 0) {
        large.front().emplace_back(st.front());
        st.clear();
      }
    }
    for (int i = 1; (i << 1) <= n / 32; i <<= 1) {
      std::vector<int> v;
      int csz = n / 32 + 1 - (i << 1);
      v.reserve(csz);
      for (int k = 0; k < csz; k++) {
        v.emplace_back(get_min(large.back()[k], large.back()[k + i]));
      }
      large.emplace_back(std::move(v));
    }
  }

  int fold(int l, int r) const {
    --r;
    int left = l / 32 + 1;
    int right = r / 32;
    if (left < right) {
      auto p = msb(right - left);
      return get_min(
          get_min((left - 1) * 32 + ctz((unsigned int)small[left * 32 - 1] &
                                        (~0U << (l % 32))),
                  large[p][left]),
          get_min(large[p][right - (1 << p)], right * 32 + ctz(small[r])));
    } else if (left == right) {
      return get_min((left - 1) * 32 + ctz((unsigned int)small[left * 32 - 1] &
                                           (~0U << (l % 32))),
                     left * 32 + ctz(small[r]));
    } else {
      return right * 32 + ctz((unsigned int)small[r] & (~0U << (l % 32)));
    }
  }
};

template <typename Comp>
LinearRMQ<Comp> get_linear_rmq(int n, const Comp& comp) {
  return LinearRMQ<Comp>(n, comp);
}
