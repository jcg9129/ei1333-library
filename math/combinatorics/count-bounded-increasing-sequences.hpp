#pragma once

#include "enumeration.hpp"

/**
 * @brief Count Bounded Increasing Sequences
 */
template <template <typename> class FPS, typename Mint>
Mint count_bounded_increasing_sequences(const vector<int> &lower_bounds,
                                        const vector<int> &upper_bounds) {
  assert(lower_bounds.size() == upper_bounds.size());
  const int n = (int)upper_bounds.size();
  if (n == 0) return Mint(1);

  vector<int> lower(lower_bounds), upper(upper_bounds);
  for (int i = 0; i < n; i++) {
    assert(lower[i] >= 0);
    assert(upper[i] >= 0);
    if (i > 0) lower[i] = max(lower[i], lower[i - 1]);
  }
  for (int i = n - 1; i-- > 0;) upper[i] = min(upper[i], upper[i + 1]);
  for (int i = 0; i < n; i++) {
    if (lower[i] > upper[i]) return Mint(0);
  }

  vector<int> bounds(n);
  for (int i = 0; i < n; i++) bounds[i] = upper[i] + 1;

  Enumeration<Mint> enumeration(n + bounds.back());

  auto convolution = [](FPS<Mint> f, const FPS<Mint> &g) {
    if (min(f.size(), g.size()) <= 32) {
      FPS<Mint> result(f.size() + g.size() - 1);
      for (int i = 0; i < (int)f.size(); i++) {
        if (f[i] == Mint(0)) continue;
        for (int j = 0; j < (int)g.size(); j++) result[i + j] += f[i] * g[j];
      }
      return result;
    }
    f *= g;
    return f;
  };

  auto propagate_rectangle = [&](const FPS<Mint> &left_edge,
                                 const FPS<Mint> &bottom_edge) {
    const int height = (int)left_edge.size();
    const int width = (int)bottom_edge.size();
    if (height == 0) return make_pair(bottom_edge, FPS<Mint>());

    FPS<Mint> top_edge(width), right_edge(height);
    const bool has_left = any_of(left_edge.begin(), left_edge.end(),
                                 [](const Mint &x) { return x != Mint(0); });
    const bool has_bottom = any_of(bottom_edge.begin(), bottom_edge.end(),
                                   [](const Mint &x) { return x != Mint(0); });

    // Left to top.
    if (has_left) {
      FPS<Mint> f(height), g(height + width);
      for (int i = 0; i < height; i++) {
        f[i] = left_edge[i] * enumeration.finv(height - 1 - i);
      }
      for (int i = 0; i < height + width; i++) g[i] = enumeration.fact(i);
      f = convolution(move(f), g);
      for (int i = 0; i < width; i++) {
        top_edge[i] += enumeration.finv(i) * f[height - 1 + i];
      }
    }

    // Bottom to top.
    if (has_bottom) {
      FPS<Mint> g(width);
      for (int i = 0; i < width; i++) {
        g[i] = enumeration.fact(height - 1 + i) * enumeration.finv(i);
      }
      auto f = convolution(bottom_edge, g);
      for (int i = 0; i < width; i++) {
        top_edge[i] += enumeration.finv(height - 1) * f[i];
      }
    }

    // Left to right.
    if (has_left) {
      FPS<Mint> g(height + width);
      for (int i = 0; i < height + width; i++) {
        g[i] = enumeration.fact(width - 1 + i) * enumeration.finv(i);
      }
      auto f = convolution(left_edge, g);
      for (int i = 0; i < height; i++) {
        right_edge[i] += enumeration.finv(width - 1) * f[i];
      }
    }

    // Bottom to right.
    if (has_bottom) {
      FPS<Mint> f(width), g(height + width);
      for (int i = 0; i < width; i++) {
        f[i] = bottom_edge[i] * enumeration.finv(width - 1 - i);
      }
      for (int i = 0; i < height + width; i++) g[i] = enumeration.fact(i);
      f = convolution(move(f), g);
      for (int i = 0; i < height; i++) {
        right_edge[i] += enumeration.finv(i) * f[width - 1 + i];
      }
    }

    return make_pair(top_edge, right_edge);
  };

  auto rec = [&](auto &self, int l, int r, int bottom,
                 const FPS<Mint> &bottom_edge,
                 const FPS<Mint> &input_left_edge) -> FPS<Mint> {
    if (l + 1 == r) {
      FPS<Mint> right_edge(bounds[l] - bottom, bottom_edge[0]);
      Mint prefix = 0;
      for (int i = 0; i < (int)input_left_edge.size(); i++) {
        prefix += input_left_edge[i];
        right_edge[i] += prefix;
      }
      return right_edge;
    }

    const int mid = (l + r) >> 1;
    const int height = bounds[mid] - bottom;

    auto left_edge =
        self(self, l, mid, bottom,
             FPS<Mint>(bottom_edge.begin(), bottom_edge.begin() + mid - l),
             input_left_edge);
    left_edge.resize(height);
    auto [top_edge, right_edge] = propagate_rectangle(
        left_edge, FPS<Mint>(bottom_edge.begin() + mid - l, bottom_edge.end()));
    right_edge.resize(bounds[r - 1] - bottom);

    auto upper_right = self(self, mid, r, bounds[mid], top_edge, FPS<Mint>());
    for (int i = 0; i < (int)upper_right.size(); i++) {
      right_edge[height + i] += upper_right[i];
    }
    return right_edge;
  };

  FPS<Mint> right_edge;
  int previous_lower = -1;
  for (int l = 0; l < n;) {
    int r = l + 1;
    while (r < n && lower[r] == lower[l]) r++;

    FPS<Mint> input_left_edge(bounds[l] - lower[l]);
    if (l == 0) {
      input_left_edge[0] = Mint(1);
    } else {
      for (int i = 0; i < (int)right_edge.size(); i++) {
        const int value = previous_lower + i;
        if (value < bounds[l]) {
          input_left_edge[max(0, value - lower[l])] += right_edge[i];
        }
      }
    }

    right_edge = rec(rec, l, r, lower[l], FPS<Mint>(r - l), input_left_edge);
    previous_lower = lower[l];
    l = r;
  }

  Mint answer = 0;
  for (auto &value : right_edge) answer += value;
  return answer;
}
