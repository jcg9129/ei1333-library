// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/compositional-inverse-of-formal-power-series.hpp"

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  FPS<mint> f(N);
  cin >> f;
  cout << compositional_inverse_of_formal_power_series<mint>(f) << "\n";
}
