// competitive-verifier: STANDALONE

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/compositional-inverse-of-formal-power-series.hpp"

using mint = modint998244353;
using Poly = FormalPowerSeriesFriendlyNTT<mint>;

Poly multiply_naive(const Poly &a, const Poly &b, int deg) {
  Poly result(deg);
  for (int i = 0; i < (int)a.size() && i < deg; i++) {
    for (int j = 0; j < (int)b.size() && i + j < deg; j++) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

Poly compose_naive(const Poly &f, const Poly &g, int deg) {
  Poly result(deg), power(deg);
  power[0] = mint(1);
  for (int i = 0; i < (int)f.size() && i < deg; i++) {
    for (int j = 0; j < deg; j++) result[j] += f[i] * power[j];
    power = multiply_naive(power, g, deg);
  }
  return result;
}

Poly compositional_inverse_naive(Poly f, int deg) {
  f.resize(deg);
  Poly result(deg);
  if (deg <= 1) return result;

  result[1] = mint(1) / f[1];
  for (int i = 2; i < deg; i++) {
    auto composed = compose_naive(f, result, i + 1);
    result[i] = -composed[i] / f[1];
  }
  return result;
}

int main() {
  Poly linear{0, 7};
  assert(compositional_inverse_of_formal_power_series<mint>(linear, 0) ==
         Poly{});
  assert(compositional_inverse_of_formal_power_series<mint>(linear, 1) ==
         Poly{0});
  assert(compositional_inverse_of_formal_power_series<mint>(linear, 2) ==
         Poly({0, mint(1) / mint(7)}));

  // x / (1 - x) and x / (1 + x) are compositional inverses.
  for (int n : {2, 3, 10, 1000}) {
    Poly f(n, mint(1));
    f[0] = 0;
    auto g = compositional_inverse_of_formal_power_series<mint>(f);
    assert(g[0] == mint(0));
    for (int i = 1; i < n; i++) {
      assert(g[i] == ((i & 1) ? mint(1) : mint(-1)));
    }
  }

  mt19937_64 rng(123456789);

  for (int n = 2; n <= 32; n++) {
    for (int rep = 0; rep < 10; rep++) {
      Poly f(n);
      do {
        f[1] = mint((int64_t)rng());
      } while (f[1] == mint(0));
      for (int i = 2; i < n; i++) f[i] = mint((int64_t)rng());

      for (int deg : {n, n + 3}) {
        auto got = compositional_inverse_of_formal_power_series<mint>(f, deg);
        auto expected = compositional_inverse_naive(f, deg);
        assert(got == expected);

        Poly padded = f;
        padded.resize(deg);
        auto composed = compose_naive(padded, got, deg);
        Poly x(deg);
        x[1] = mint(1);
        assert(composed == x);
      }
    }
  }
}
