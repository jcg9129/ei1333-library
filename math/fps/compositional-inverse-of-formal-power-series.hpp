#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>

#include "enumerate-coefficients-of-powers.hpp"

/**
 * @brief Compositional Inverse of Formal Power Series
 *
 * Returns g(x) such that f(g(x)) = x mod x^deg.
 * Requires f(0) = 0 and f'(0) != 0.
 *
 * @note This implementation requires an NTT-friendly modulus.
 * @complexity O(deg std::log^2 deg)
 */
template <typename Mint>
FormalPowerSeriesFriendlyNTT<Mint> compositional_inverse_of_formal_power_series(
    FormalPowerSeriesFriendlyNTT<Mint> f, int deg = -1) {
  using Poly = FormalPowerSeriesFriendlyNTT<Mint>;

  if (deg == -1) deg = (int)f.size();
  assert(deg >= 0);
  if (deg == 0) return {};
  assert((int)f.size() >= 2);
  assert(f[0] == Mint(0));
  assert(f[1] != Mint(0));

  f.resize(deg);
  if (deg == 1) return Poly(1, Mint(0));

  const int n = deg - 1;
  assert((std::uint64_t)n < Mint::mod());

  Poly h = enumerate_coefficients_of_powers<Mint>(f);
  h *= Mint(n);

  std::vector<Mint> inverse(n + 1);
  inverse[1] = Mint(1);
  for (int i = 2; i <= n; i++) {
    inverse[i] = -inverse[Mint::mod() % i] * Mint(Mint::mod() / i);
  }
  for (int i = 1; i <= n; i++) h[i] *= inverse[i];

  h = h.rev();
  h *= Mint(1) / h[0];

  Poly g = (h.log(n) * (Mint(1) / Mint(-n))).exp(n);
  g *= Mint(1) / f[1];
  g = g << 1;
  g.resize(deg);
  return g;
}
