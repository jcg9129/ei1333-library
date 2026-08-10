// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series
// clang-format on

#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

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
  FPS<mint> F(N);
  read_sequence(F);
  print_sequence(F.inv());
}
