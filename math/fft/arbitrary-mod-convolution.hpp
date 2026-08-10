#pragma once

#include <cstdint>
#include <vector>

#include "fast-fourier-transform.hpp"

/*
 * @brief Arbitrary Mod Convolution(任意mod畳み込み)
 */
template <typename T>
struct ArbitraryModConvolution {
  using real = FastFourierTransform::real;
  using C = FastFourierTransform::C;

  ArbitraryModConvolution() = default;

  static std::vector<T> multiply(const std::vector<T>& a,
                                 const std::vector<T>& b, int need = -1) {
    if (need == -1) need = a.size() + b.size() - 1;
    int nbase = 0;
    while ((1 << nbase) < need) nbase++;
    FastFourierTransform::ensure_base(nbase);
    int sz = 1 << nbase;
    std::vector<C> fa(sz);
    for (int i = 0; i < a.size(); i++) {
      fa[i] = C(a[i].val() & ((1 << 15) - 1), a[i].val() >> 15);
    }
    fft(fa, sz);
    std::vector<C> fb(sz);
    if (a == b) {
      fb = fa;
    } else {
      for (int i = 0; i < b.size(); i++) {
        fb[i] = C(b[i].val() & ((1 << 15) - 1), b[i].val() >> 15);
      }
      fft(fb, sz);
    }
    real ratio = 0.25 / sz;
    C r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for (int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      C a1 = (fa[i] + fa[j].conj());
      C a2 = (fa[i] - fa[j].conj()) * r2;
      C b1 = (fb[i] + fb[j].conj()) * r3;
      C b2 = (fb[i] - fb[j].conj()) * r4;
      if (i != j) {
        C c1 = (fa[j] + fa[i].conj());
        C c2 = (fa[j] - fa[i].conj()) * r2;
        C d1 = (fb[j] + fb[i].conj()) * r3;
        C d2 = (fb[j] - fb[i].conj()) * r4;
        fa[i] = c1 * d1 + c2 * d2 * r5;
        fb[i] = c1 * d2 + c2 * d1;
      }
      fa[j] = a1 * b1 + a2 * b2 * r5;
      fb[j] = a1 * b2 + a2 * b1;
    }
    fft(fa, sz);
    fft(fb, sz);
    std::vector<T> ret(need);
    for (int i = 0; i < need; i++) {
      std::int64_t aa = std::llround(fa[i].x);
      std::int64_t bb = std::llround(fb[i].x);
      std::int64_t cc = std::llround(fa[i].y);
      aa = T(aa).val(), bb = T(bb).val(), cc = T(cc).val();
      ret[i] = aa + (bb << 15) + (cc << 30);
    }
    return ret;
  }
};
