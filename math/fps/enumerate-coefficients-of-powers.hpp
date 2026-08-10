#pragma once

#include <cassert>
#include <cmath>
#include <iterator>
#include <utility>
#include <vector>

#include "formal-power-series-friendly-ntt.hpp"

/**
 * @brief Enumerate Coefficients of Powers of Formal Power Series
 *
 * Returns [x^n] f(x)^k g(x) for k = 0, 1, ..., m, where n = f.size() - 1.
 *
 * @note This implementation requires an NTT-friendly modulus.
 * @note The implementation is based on the fast power-projection algorithm
 *       used for FPS composition/compositional inverse.
 * @complexity O(n std::log^2 n + m std::log m)
 */
template <typename Mint>
FormalPowerSeriesFriendlyNTT<Mint> enumerate_coefficients_of_powers(
    FormalPowerSeriesFriendlyNTT<Mint> f,
    FormalPowerSeriesFriendlyNTT<Mint> g = {Mint(1)}, int m = -1) {
  using Poly = FormalPowerSeriesFriendlyNTT<Mint>;
  using NTT = NumberTheoreticTransformFriendlyModInt<Mint>;

  assert(!f.empty());
  int n = (int)f.size() - 1;
  int k = 1;
  g.resize(n + 1);
  if (m == -1) m = n;
  assert(m >= 0);

  int h = 1;
  while (h < n + 1) h <<= 1;

  NTT::init();
  // The largest transform has length 2 * h.
  assert(1 + __builtin_ctz(h) <= NTT::max_base);

  Poly P((n + 1) * k), Q((n + 1) * k), next_P, next_Q;
  Poly buffer, doubled;

  for (int i = 0; i <= n; i++) P[i * k] = g[i];
  for (int i = 0; i <= n; i++) Q[i * k] = -f[i];
  Q[0] += Mint(1);

  const Mint inv_two = Mint(1) / Mint(2);
  const Mint two = Mint(2);
  Mint inv_k = Mint(1);
  Mint inv_h = Mint(1) / Mint(h);

  while (n > 0) {
    // If a contains the length-k NTT of A(x), append the evaluations at the
    // odd 2k-th roots and turn it into the length-2k NTT of A(x).
    auto ntt_doubling = [&](Poly& a) {
      assert((int)a.size() == k);
      doubled = a;
      NTT::intt(doubled, false);

      const Mint zeta = NTT::roots[__builtin_ctz(2 * k)];
      Mint power = inv_k;
      for (int i = 0; i < k; i++) {
        doubled[i] *= power;
        power *= zeta;
      }
      NTT::ntt(doubled);
      a.insert(a.end(), doubled.begin(), doubled.end());
    };

    next_P.clear();
    next_Q.clear();
    next_P.reserve((n + 1) * 2 * k);
    next_Q.reserve((n + 1) * 2 * k);

    for (int i = 0; i <= n; i++) {
      buffer.assign(P.begin() + i * k, P.begin() + (i + 1) * k);
      ntt_doubling(buffer);
      next_P.insert(next_P.end(), buffer.begin(), buffer.end());

      buffer.assign(Q.begin() + i * k, Q.begin() + (i + 1) * k);
      if (i == 0) {
        // Q has a distinguished constant 1. Remove it before doubling and
        // restore it in the two halves afterwards.
        for (int j = 0; j < k; j++) buffer[j] -= Mint(1);
        ntt_doubling(buffer);
        for (int j = 0; j < k; j++) buffer[j] += Mint(1);
        for (int j = 0; j < k; j++) buffer[k + j] -= Mint(1);
      } else {
        ntt_doubling(buffer);
      }
      next_Q.insert(next_Q.end(), buffer.begin(), buffer.end());
    }

    // Pad the x direction to length 2h for every frequency in the other
    // variable. h * k stays constant, so the total working size is linear.
    next_P.resize(4 * h * k);
    next_Q.resize(4 * h * k);

    Poly p(2 * h), q(2 * h);
    const Mint inverse_zeta = NTT::iroots[__builtin_ctz(2 * h)];

    std::vector<int> bit_reversal;
    if (n & 1) {
      bit_reversal.resize(h);
      const int log_h = __builtin_ctz(h);
      for (int i = 0; i < h; i++) {
        bit_reversal[i] =
            (bit_reversal[i >> 1] >> 1) + ((i & 1) << (log_h - 1));
      }
    }

    for (int frequency = 0; frequency < 2 * k; frequency++) {
      p.assign(2 * h, Mint(0));
      q.assign(2 * h, Mint(0));
      for (int i = 0; i < h; i++) {
        p[i] = next_P[i * 2 * k + frequency];
        q[i] = next_Q[i * 2 * k + frequency];
      }

      NTT::ntt(p);
      NTT::ntt(q);

      // In this radix-4 DIF ordering, changing x to -x swaps adjacent NTT
      // values.
      for (int i = 0; i < 2 * h; i += 2) std::swap(q[i], q[i + 1]);
      for (int i = 0; i < 2 * h; i++) p[i] *= q[i];
      for (int i = 0; i < h; i++) q[i] = q[2 * i] * q[2 * i + 1];

      if ((n & 1) == 0) {
        for (int i = 0; i < h; i++) {
          p[i] = (p[2 * i] + p[2 * i + 1]) * inv_two;
        }
      } else {
        Mint coefficient = inv_two;
        buffer.resize(h);
        for (int i : bit_reversal) {
          buffer[i] = (p[2 * i] - p[2 * i + 1]) * coefficient;
          coefficient *= inverse_zeta;
        }
        p.swap(buffer);
      }

      p.resize(h);
      q.resize(h);
      NTT::intt(p, false);
      NTT::intt(q, false);

      for (int i = 0; i < h; i++) {
        next_P[i * 2 * k + frequency] = p[i] * inv_h;
        next_Q[i * 2 * k + frequency] = q[i] * inv_h;
      }
    }

    next_P.resize((n / 2 + 1) * 2 * k);
    next_Q.resize((n / 2 + 1) * 2 * k);
    P.swap(next_P);
    Q.swap(next_Q);

    n /= 2;
    h /= 2;
    k *= 2;
    inv_h *= two;
    inv_k *= inv_two;
  }

  Poly numerator(P.begin(), P.begin() + k);
  NTT::intt(numerator, false);
  for (auto& value : numerator) value *= inv_k;

  if (f[0] == Mint(0)) {
    auto result = numerator.rev().pre(m + 1);
    result.resize(m + 1);
    return result;
  }

  Poly denominator(Q.begin(), Q.begin() + k);
  NTT::intt(denominator, false);
  for (auto& value : denominator) value *= inv_k;
  denominator[0] -= Mint(1);

  Poly shifted_one(k + 1);
  shifted_one[k] = Mint(1);
  auto reversed_numerator = numerator.rev().pre(m + 1);
  auto reversed_denominator = (denominator + shifted_one).rev().pre(m + 1);
  auto result =
      (reversed_numerator * reversed_denominator.inv(m + 1)).pre(m + 1);
  result.resize(m + 1);
  return result;
}
