#pragma once

#include "formal-power-series-friendly-ntt.hpp"

/**
 * @brief Composition of Formal Power Series
 *
 * Returns outer(inner(x)) modulo x^deg. Missing coefficients are treated as
 * zero, and the returned formal power series has exactly deg coefficients.
 *
 * This is the transposed power-projection algorithm. The two-dimensional
 * transforms are kept in NTT representation between recursive levels.
 *
 * @note This implementation requires an NTT-friendly modulus.
 * @complexity O(deg log^2 deg)
 */
template <typename Mint>
FormalPowerSeriesFriendlyNTT<Mint> composition_of_formal_power_series(
    const FormalPowerSeriesFriendlyNTT<Mint>& outer,
    const FormalPowerSeriesFriendlyNTT<Mint>& inner, int deg = -1) {
  using Poly = FormalPowerSeriesFriendlyNTT<Mint>;
  using NTT = NumberTheoreticTransformFriendlyModInt<Mint>;

  if (deg == -1) deg = (int)outer.size();
  assert(deg >= 0);
  if (deg == 0) return {};
  assert(inner.empty() || inner[0] == Mint(0));

  if (deg == 1) {
    return Poly{outer.empty() ? Mint(0) : outer[0]};
  }

  const int result_size = deg;
  int size = 1;
  while (size < result_size) size <<= 1;

  NTT::init();
  assert(__builtin_ctz(size) + 1 <= NTT::max_base);

  vector<Mint> f(size), g(size);
  copy_n(outer.begin(), min((int)outer.size(), result_size), f.begin());
  copy_n(inner.begin(), min((int)inner.size(), result_size), g.begin());

  // W is the table of powers of a primitive 2*size-th inverse root, stored in
  // the bit-reversed order used by the radix-4 NTT. inverse_w stores W^{-1}.
  vector<Mint> w(size), inverse_w(size);
  vector<int> bit_reverse(size);
  const int lg = __builtin_ctz(size);
  for (int i = 1; i < size; i++) {
    bit_reverse[i] = (bit_reverse[i >> 1] >> 1) | ((i & 1) << (lg - 1));
  }
  const Mint dw = NTT::iroots[lg + 1];
  const Mint inverse_dw = NTT::roots[lg + 1];
  Mint power = 1, inverse_power = 1;
  for (int index : bit_reverse) {
    w[index] = power;
    inverse_w[index] = inverse_power;
    power *= dw;
    inverse_power *= inverse_dw;
  }

  auto rec = [&](auto& self, int n, int k,
                 vector<Mint>& denominator) -> vector<Mint> {
    // n * k is invariant and is equal to size.
    assert((int)denominator.size() == 4 * n * k);

    if (n == 1) {
      reverse(f.begin(), f.end());
      NTT::transposed_intt(f);
      const Mint coefficient = Mint(1) / Mint(k);
      for (auto& value : f) value *= coefficient;

      vector<Mint> result(4 * k);
      for (int i = 0; i < k; i++) result[2 * i] = f[i];
      return result;
    }

    auto double_y = [&](vector<Mint>& values, int left, int right,
                        bool transpose) -> void {
      const Mint z = inverse_w[k / 2];
      vector<Mint> buffer(k);

      if (!transpose) {
        for (int x = left; x < right; x++) {
          for (int y = 0; y < k; y++) {
            buffer[y] = values[2 * n * y + x];
          }
          NTT::intt(buffer);
          Mint multiplier = 1;
          for (int y = 1; y < k; y++) {
            multiplier *= z;
            buffer[y] *= multiplier;
          }
          NTT::ntt(buffer);
          for (int y = 0; y < k; y++) {
            values[2 * n * (k + y) + x] = buffer[y];
          }
        }
      } else {
        for (int x = left; x < right; x++) {
          for (int y = 0; y < k; y++) {
            buffer[y] = values[2 * n * (k + y) + x];
          }
          NTT::transposed_ntt(buffer);
          Mint multiplier = 1;
          for (int y = 1; y < k; y++) {
            multiplier *= z;
            buffer[y] *= multiplier;
          }
          NTT::transposed_intt(buffer);
          for (int y = 0; y < k; y++) {
            values[2 * n * y + x] += buffer[y];
          }
        }
      }
    };

    auto transform_x = [&](vector<Mint>& values, int left, int right,
                           bool transpose) -> void {
      vector<Mint> buffer(2 * n);
      for (int y = left; y < right; y++) {
        copy_n(values.begin() + (size_t)2 * n * y, 2 * n, buffer.begin());
        if (transpose) {
          NTT::transposed_ntt(buffer);
        } else {
          NTT::ntt(buffer);
        }
        copy(buffer.begin(), buffer.end(), values.begin() + (size_t)2 * n * y);
      }
    };

    // Transform the denominator in both variables. The order is selected so
    // that the smaller number of transforms is performed before doubling.
    if (n <= k) {
      double_y(denominator, 1, n, false);
      transform_x(denominator, 0, 2 * k, false);
    } else {
      transform_x(denominator, 0, k, false);
      double_y(denominator, 0, 2 * n, false);
    }

    for (int i = 0; i < 2 * n * k; i++) denominator[i] += Mint(1);
    for (int i = 2 * n * k; i < 4 * n * k; i++) {
      denominator[i] -= Mint(1);
    }

    vector<Mint> next_denominator(4 * n * k);
    vector<Mint> reduced_row(n);
    for (int y = 0; y < 2 * k; y++) {
      const auto row = denominator.begin() + (size_t)2 * n * y;
      for (int x = 0; x < n; x++) {
        reduced_row[x] = row[2 * x] * row[2 * x + 1];
      }
      NTT::intt(reduced_row);
      copy_n(reduced_row.begin(), n / 2,
             next_denominator.begin() + (size_t)n * y);
    }
    for (int y = 0; y < 4 * k; y++) {
      next_denominator[(size_t)n * y] = Mint(0);
    }

    auto result = self(self, n / 2, k * 2, next_denominator);

    vector<Mint> buffer(n), reconstructed(2 * n);
    for (int y = 2 * k; y-- > 0;) {
      copy_n(result.begin() + (size_t)n * y, n / 2, buffer.begin());
      fill(buffer.begin() + n / 2, buffer.end(), Mint(0));
      NTT::transposed_intt(buffer);

      const auto row = denominator.begin() + (size_t)2 * n * y;
      for (int x = 0; x < n; x++) {
        buffer[x] *= w[x];
        reconstructed[2 * x] = row[2 * x + 1] * buffer[x];
        reconstructed[2 * x + 1] = -row[2 * x] * buffer[x];
      }
      copy(reconstructed.begin(), reconstructed.end(),
           result.begin() + (size_t)2 * n * y);
    }

    // Apply the transposes in reverse order.
    if (n <= k) {
      transform_x(result, 0, 2 * k, true);
      double_y(result, 0, n, true);
    } else {
      double_y(result, 0, 2 * n, true);
      transform_x(result, 0, k, true);
    }

    return result;
  };

  vector<Mint> denominator(4 * size);
  for (int i = 0; i < size; i++) denominator[i] = -g[i];

  auto result = rec(rec, size, 1, denominator);
  result.resize(size);
  reverse(result.begin(), result.end());
  result.resize(result_size);
  return Poly(result.begin(), result.end());
}
