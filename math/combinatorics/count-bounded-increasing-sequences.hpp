#pragma once

#include "../fft/number-theoretic-transform-friendly-mod-int.hpp"
#include "enumeration.hpp"

/**
 * @brief Count Bounded Increasing Sequences
 */
template <typename Mint>
Mint count_bounded_increasing_sequences(const vector<int> &lower_bounds,
                                        const vector<int> &upper_bounds) {
  using NTT = NumberTheoreticTransformFriendlyModInt<Mint>;

  assert(lower_bounds.size() == upper_bounds.size());
  const int original_n = static_cast<int>(upper_bounds.size());
  if (original_n == 0) return Mint(1);

  vector<int> lower(lower_bounds), upper(upper_bounds);
  for (int i = 0; i < original_n; i++) {
    assert(lower[i] >= 0);
    assert(upper[i] >= 0);
    if (i > 0) lower[i] = max(lower[i], lower[i - 1]);
  }
  for (int i = original_n - 1; i-- > 0;) {
    upper[i] = min(upper[i], upper[i + 1]);
  }
  for (int i = 0; i < original_n; i++) {
    if (lower[i] >= upper[i]) return Mint(0);
    --upper[i];
  }

  // Shift the lower boundary one column to the right and translate by L[0].
  const int base = lower[0];
  const int n = original_n + 1;
  vector<int> lower_boundary(n), upper_boundary(n);
  lower_boundary[0] = 0;
  for (int i = 0; i < original_n; i++) {
    lower_boundary[i + 1] = lower[i] - base;
    upper_boundary[i] = upper[i] - base;
  }
  // A terminal vertical edge. The extra height does not change the answer.
  upper_boundary[original_n] = upper.back() - base + 1;

  const int max_factorial = n + upper_boundary.back() + 5;
  assert(static_cast<uint64_t>(max_factorial) < Mint::mod());
  Enumeration<Mint> enumeration(max_factorial);

  // Compute only the first `limit` coefficients.
  auto convolution_prefix = [&](vector<Mint> f, vector<Mint> g, int limit) {
    assert(limit >= 0);
    if (limit == 0) return vector<Mint>();
    assert(!f.empty() && !g.empty());
    if (static_cast<int>(f.size()) > limit) f.resize(limit);
    if (static_cast<int>(g.size()) > limit) g.resize(limit);

    if (min(f.size(), g.size()) <= 32) {
      vector<Mint> result(limit);
      for (int i = 0; i < static_cast<int>(f.size()); i++) {
        if (f[i] == Mint(0)) continue;
        const int m = min<int>(static_cast<int>(g.size()), limit - i);
        for (int j = 0; j < m; j++) result[i + j] += f[i] * g[j];
      }
      return result;
    }

    auto result = NTT::multiply(std::move(f), std::move(g));
    result.resize(limit);
    return result;
  };

  auto propagate_rectangle = [&](const vector<Mint> &left_edge,
                                 const vector<Mint> &bottom_edge) {
    const int height = static_cast<int>(left_edge.size());
    const int width = static_cast<int>(bottom_edge.size());
    assert(width > 0);
    if (height == 0) {
      return make_pair(bottom_edge, vector<Mint>());
    }

    vector<Mint> top_edge(width), right_edge(height);
    const bool has_left = any_of(left_edge.begin(), left_edge.end(),
                                 [](const Mint &x) { return x != Mint(0); });
    const bool has_bottom = any_of(bottom_edge.begin(), bottom_edge.end(),
                                   [](const Mint &x) { return x != Mint(0); });

    // Left -> top and bottom -> right are middle products with the same
    // factorial kernel. A cyclic convolution of length >= height + width - 1
    // computes the required middle coefficients without wraparound.
    if (has_left || has_bottom) {
      if (min(height, width) <= 32) {
        if (has_left) {
          vector<Mint> scaled(height);
          for (int k = 0; k < height; k++) {
            scaled[k] = left_edge[height - 1 - k] * enumeration.finv(k);
          }
          for (int j = 0; j < width; j++) {
            Mint sum = 0;
            for (int k = 0; k < height; k++) {
              sum += scaled[k] * enumeration.fact(j + k);
            }
            top_edge[j] += sum * enumeration.finv(j);
          }
        }
        if (has_bottom) {
          vector<Mint> scaled(width);
          for (int k = 0; k < width; k++) {
            scaled[k] = bottom_edge[width - 1 - k] * enumeration.finv(k);
          }
          for (int j = 0; j < height; j++) {
            Mint sum = 0;
            for (int k = 0; k < width; k++) {
              sum += scaled[k] * enumeration.fact(j + k);
            }
            right_edge[j] += sum * enumeration.finv(j);
          }
        }
      } else {
        int size = 1;
        while (size < height + width - 1) size <<= 1;

        vector<Mint> kernel(size);
        for (int i = 0; i < height + width - 1; i++) {
          kernel[i] = enumeration.fact(i);
        }
        NTT::ntt(kernel);

        // Fold the inverse-transform normalization into the shared kernel.
        const Mint inv_size = Mint(1) / Mint(size);
        for (auto &x : kernel) x *= inv_size;

        auto apply_middle_product = [&](const vector<Mint> &input,
                                        vector<Mint> &output) {
          const int input_size = static_cast<int>(input.size());
          vector<Mint> f(size);
          f[0] = input[input_size - 1];
          for (int k = 1; k < input_size; k++) {
            f[size - k] = input[input_size - 1 - k] * enumeration.finv(k);
          }
          NTT::ntt(f);
          for (int i = 0; i < size; i++) f[i] *= kernel[i];
          NTT::intt(f, false);
          for (int i = 0; i < static_cast<int>(output.size()); i++) {
            output[i] += f[i] * enumeration.finv(i);
          }
        };

        if (has_left) apply_middle_product(left_edge, top_edge);
        if (has_bottom) apply_middle_product(bottom_edge, right_edge);
      }
    }

    // Bottom -> top.
    if (has_bottom) {
      vector<Mint> kernel(width);
      for (int i = 0; i < width; i++) {
        kernel[i] = enumeration.fact(height - 1 + i) * enumeration.finv(i);
      }
      auto f = convolution_prefix(bottom_edge, std::move(kernel), width);
      const Mint coefficient = enumeration.finv(height - 1);
      for (int i = 0; i < width; i++) top_edge[i] += coefficient * f[i];
    }

    // Left -> right.
    if (has_left) {
      vector<Mint> kernel(height);
      for (int i = 0; i < height; i++) {
        kernel[i] = enumeration.fact(width - 1 + i) * enumeration.finv(i);
      }
      auto f = convolution_prefix(left_edge, std::move(kernel), height);
      const Mint coefficient = enumeration.finv(width - 1);
      for (int i = 0; i < height; i++) right_edge[i] += coefficient * f[i];
    }

    return make_pair(top_edge, right_edge);
  };

  // Solve a one-sided staircase. `heights` must be nondecreasing, and
  // `start[i]` is an additive source at the i-th bottom-edge vertex.
  auto solve_one_sided = [&](const vector<int> &heights,
                             const vector<Mint> &start) -> vector<Mint> {
    const int size = static_cast<int>(heights.size());
    assert(size > 0);
    assert(static_cast<int>(start.size()) == size);

    vector<int> bounds(size);
    for (int i = 0; i < size; i++) {
      assert(heights[i] >= 0);
      if (i > 0) assert(heights[i - 1] <= heights[i]);
      bounds[i] = heights[i] + 1;
    }

    auto rec = [&](auto &self, int l, int r, int bottom,
                   const vector<Mint> &bottom_edge) -> vector<Mint> {
      assert(static_cast<int>(bottom_edge.size()) == r - l);
      if (l + 1 == r) {
        return vector<Mint>(bounds[l] - bottom, bottom_edge[0]);
      }

      const int mid = (l + r) >> 1;
      const int height = bounds[mid] - bottom;

      auto left_edge = self(
          self, l, mid, bottom,
          vector<Mint>(bottom_edge.begin(), bottom_edge.begin() + mid - l));
      left_edge.resize(height);

      auto [top_edge, right_edge] = propagate_rectangle(
          left_edge,
          vector<Mint>(bottom_edge.begin() + mid - l, bottom_edge.end()));
      right_edge.resize(bounds[r - 1] - bottom);

      auto upper_right = self(self, mid, r, bounds[mid], top_edge);
      for (int i = 0; i < static_cast<int>(upper_right.size()); i++) {
        right_edge[height + i] += upper_right[i];
      }
      return right_edge;
    };

    return rec(rec, 0, size, 0, start);
  };

  // Decompose the corridor into alternating horizontal and vertical
  // one-sided staircases. Vertical pieces are transposed.
  const int distance = static_cast<int>(ranges::upper_bound(lower_boundary, 0) -
                                        lower_boundary.begin());
  int px = 0, py = 0;
  int qx = distance - 1, qy = 0;
  if (qx == 0) qy = upper_boundary[0];

  vector<Mint> current(abs(qx - px) + abs(qy - py) + 1);
  current[0] = Mint(1);
  bool first_piece = true;

  while (qx != n - 1 || qy != upper_boundary[n - 1]) {
    // Boundary DP values are prefix sums of additive sources.
    if (!first_piece) {
      for (int i = static_cast<int>(current.size()) - 1; i >= 1; i--) {
        current[i] -= current[i - 1];
      }
    }
    first_piece = false;

    if (py == qy) {
      vector<int> heights(qx - px + 1);
      for (int i = 0; i <= qx - px; i++) {
        heights[i] = upper_boundary[px + i] - py;
      }
      current = solve_one_sided(heights, std::move(current));
      px = qx;
      py = qy;
      qy = upper_boundary[qx];
    } else {
      // qx + 1 is the first lower-boundary index above py. The pointer moves
      // monotonically over this vertical segment.
      int x = qx + 1;
      const int base_x = x;
      vector<int> heights(qy - py + 1);
      for (int i = 0; i <= qy - py; i++) {
        const int y = py + i;
        while (x < n && lower_boundary[x] <= y) ++x;
        heights[i] = x - base_x;
      }
      current = solve_one_sided(heights, std::move(current));
      px = qx;
      py = qy;
      qx = x - 1;
    }
  }

  return current.back();
}
