#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "../others/binary-indexed-tree.hpp"
#include "succinct-indexable-dictionary.hpp"

/*
 * @brief Wavelet Matrix Point Add Rectangle Sum
 *
 */
template <typename T, int MAXLOG, typename D>
struct WaveletMatrixPointAddRectangleSum {
  std::size_t length;
  SuccinctIndexableDictionary matrix[MAXLOG];
  BinaryIndexedTree<D> ds[MAXLOG];
  std::vector<T> v;
  int mid[MAXLOG];

  WaveletMatrixPointAddRectangleSum() = default;

  WaveletMatrixPointAddRectangleSum(const std::vector<T>& v,
                                    const std::vector<D>& d)
      : length(v.size()), v(v) {
    assert(v.size() == d.size());
    std::vector<int> l(length), r(length), ord(length);
    std::iota(std::begin(ord), std::end(ord), 0);
    std::vector<D> dd(length);
    for (int level = MAXLOG - 1; level >= 0; level--) {
      matrix[level] = SuccinctIndexableDictionary(length + 1);
      int left = 0, right = 0;
      for (int i = 0; i < length; i++) {
        if (((v[ord[i]] >> level) & 1)) {
          matrix[level].set(i);
          r[right++] = ord[i];
        } else {
          l[left++] = ord[i];
        }
      }
      mid[level] = left;
      matrix[level].build();
      std::swap(ord, l);
      for (int i = 0; i < right; i++) {
        ord[left + i] = r[i];
      }
      for (int i = 0; i < length; i++) {
        dd[i] = d[ord[i]];
      }
      ds[level] = BinaryIndexedTree<D>(dd);
    }
  }

  std::pair<int, int> succ(bool f, int l, int r, int level) {
    return {matrix[level].rank(f, l) + mid[level] * f,
            matrix[level].rank(f, r) + mid[level] * f};
  }

  // count d[i] s.t. (l <= i < r) && (v[i] < upper)
  D rect_sum(int l, int r, T upper) {
    D ret = 0;
    for (int level = MAXLOG - 1; level >= 0; level--) {
      if (((upper >> level) & 1)) {
        auto nxt = succ(false, l, r, level);
        ret += ds[level].prod(nxt.first, nxt.second);
        l = l - nxt.first + mid[level];
        r = r - nxt.second + mid[level];
      } else {
        std::tie(l, r) = succ(false, l, r, level);
      }
    }
    return ret;
  }

  D rect_sum(int l, int r, T lower, T upper) {
    return rect_sum(l, r, upper) - rect_sum(l, r, lower);
  }

  void point_add(int k, const D& x) {
    auto& y = v[k];
    for (int level = MAXLOG - 1; level >= 0; level--) {
      bool f = ((y >> level) & 1);
      k = matrix[level].rank(f, k) + mid[level] * f;
      ds[level].apply(k, x);
    }
  }
};

template <typename T, int MAXLOG, typename D>
struct CompressedWaveletMatrixPointAddRectangleSum {
  WaveletMatrixPointAddRectangleSum<int, MAXLOG, D> mat;
  std::vector<T> ys;

  CompressedWaveletMatrixPointAddRectangleSum(const std::vector<T>& v,
                                              const std::vector<D>& d)
      : ys(v) {
    std::sort(std::begin(ys), std::end(ys));
    ys.erase(std::unique(std::begin(ys), std::end(ys)), std::end(ys));
    std::vector<int> t(v.size());
    for (int i = 0; i < v.size(); i++) t[i] = get(v[i]);
    mat = WaveletMatrixPointAddRectangleSum<int, MAXLOG, D>(t, d);
  }

  inline int get(const T& x) {
    return std::lower_bound(std::begin(ys), std::end(ys), x) - std::begin(ys);
  }

  D rect_sum(int l, int r, T upper) { return mat.rect_sum(l, r, get(upper)); }

  D rect_sum(int l, int r, T lower, T upper) {
    return mat.rect_sum(l, r, get(lower), get(upper));
  }

  void point_add(int k, const D& x) { mat.point_add(k, x); }
};
