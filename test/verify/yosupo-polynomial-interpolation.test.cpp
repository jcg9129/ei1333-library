// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_interpolation
// clang-format on

#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/polynomial-interpolation.hpp"

using namespace std;

using mint = modint998244353;

template <typename Sequence>
void read_sequence(Sequence& values) {
  for (auto& value : values) cin >> value;
}

template <typename Sequence>
void print_sequence(const Sequence& values) {
  for (int i = 0; i < static_cast<int>(values.size()); i++) {
    if (i > 0) cout << " ";
    cout << values[i];
  }
  cout << "\n";
}

int main() {
  int N;
  cin >> N;
  FPS<mint> xs(N), ys(N);
  read_sequence(xs);
  read_sequence(ys);
  print_sequence(polynomial_interpolation(xs, ys));
}
