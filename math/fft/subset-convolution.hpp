#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <utility>
#include <vector>

/**
 * @brief Subset Convolution
 */
template <typename Mint, int _s>
struct SubsetConvolution {
  using fps = std::array<Mint, _s + 1>;
  static std::array<int, (1 << _s)> pop_count;
  static constexpr int s = _s;

  SubsetConvolution() = default;

  static void init() {
    if (pop_count.back() == 0) {
      pop_count[0] = 0;
      for (int i = 1; i < (1 << s); i++) {
        pop_count[i] = pop_count[i - (i & -i)] + 1;
      }
    }
  }

  static inline void add(fps& f, const fps& g, int d) {
    for (int i = 0; i < d; i++) {
      f[i] += g[i];
    }
  }

  static inline void sub(fps& f, const fps& g, int d) {
    for (int i = d; i <= s; i++) {
      f[i] -= g[i];
    }
  }

  static void zeta_transform(std::vector<fps>& F) {
    const int n = (int)F.size();
    assert((n & (n - 1)) == 0);
    init();
    for (int i = 1; i < n; i <<= 1) {
      for (int j = 0; j < n; j += i << 1) {
        for (int k = 0; k < i; k++) {
          add(F[j + k + i], F[j + k], pop_count[j + k + i]);
        }
      }
    }
  }

  static void moebius_transform(std::vector<fps>& F) {
    const int n = (int)F.size();
    assert((n & (n - 1)) == 0);
    init();
    for (int i = 1; i < n; i <<= 1) {
      for (int j = 0; j < n; j += i << 1) {
        for (int k = 0; k < i; k++) {
          sub(F[j + k + i], F[j + k], pop_count[j + k + i]);
        }
      }
    }
  }

  static std::vector<fps> lift(const std::vector<Mint>& f) {
    const int n = (int)f.size();
    init();
    std::vector<fps> F(n);
    for (int i = 0; i < n; i++) {
      std::fill(F[i].begin(), F[i].end(), Mint());
      F[i][pop_count[i]] = f[i];
    }
    return F;
  }

  static std::vector<Mint> unlift(const std::vector<fps>& F) {
    const int n = (int)F.size();
    init();
    std::vector<Mint> f(n);
    for (int i = 0; i < (int)F.size(); i++) {
      f[i] = F[i][pop_count[i]];
    }
    return f;
  }

  static void prod(std::vector<fps>& F, const std::vector<fps>& G) {
    int n = (int)F.size();
    int d = __builtin_ctz(n);
    for (int i = 0; i < n; i++) {
      fps h{};
      for (int j = 0; j <= d; j++) {
        for (int k = 0; k <= d - j; k++) {
          h[j + k] += F[i][j] * G[i][k];
        }
      }
      F[i] = std::move(h);
    }
  }

  static std::vector<Mint> multiply(const std::vector<Mint>& f,
                                    const std::vector<Mint>& g) {
    auto F = lift(f), G = lift(g);
    zeta_transform(F);
    zeta_transform(G);
    prod(F, G);
    moebius_transform(F);
    return unlift(F);
  }
};

template <typename Mint, int s>
std::array<int, (1 << s)> SubsetConvolution<Mint, s>::pop_count;
