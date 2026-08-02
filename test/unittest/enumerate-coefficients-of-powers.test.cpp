// competitive-verifier: STANDALONE

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/enumerate-coefficients-of-powers.hpp"

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

Poly enumerate_coefficients_of_powers_naive(const Poly &f, const Poly &g,
                                             int m) {
  const int n = (int)f.size() - 1;
  Poly result(m + 1), power(n + 1);
  power[0] = mint(1);
  for (int i = 0; i <= m; i++) {
    result[i] = multiply_naive(power, g, n + 1)[n];
    power = multiply_naive(power, f, n + 1);
  }
  return result;
}

int main() {
  mt19937_64 rng(123456789);

  for (int n = 0; n <= 20; n++) {
    for (int rep = 0; rep < 20; rep++) {
      for (int nonzero_constant = 0; nonzero_constant < 2;
           nonzero_constant++) {
        Poly f(n + 1), g(n + 1);
        if (nonzero_constant) {
          do {
            f[0] = mint((int64_t)rng());
          } while (f[0] == mint(0));
        }
        for (int i = 1; i <= n; i++) f[i] = mint((int64_t)rng());
        for (auto &value : g) value = mint((int64_t)rng());

        const int m = rng() % (2 * n + 6);
        assert(enumerate_coefficients_of_powers<mint>(f, g, m) ==
               enumerate_coefficients_of_powers_naive(f, g, m));
      }
    }
  }
}
