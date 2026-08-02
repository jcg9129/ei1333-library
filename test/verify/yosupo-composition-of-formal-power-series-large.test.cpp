// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/composition_of_formal_power_series_large

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/composition-of-formal-power-series.hpp"

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  FPS<mint> F(N), G(N);
  cin >> F >> G;
  cout << composition_of_formal_power_series<mint>(F, G) << "\n";
}
