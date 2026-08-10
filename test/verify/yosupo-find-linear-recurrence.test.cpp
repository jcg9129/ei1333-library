// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/find_linear_recurrence
// clang-format on

#include <algorithm>
#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/berlekamp-massey.hpp"
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
  FPS<mint> a(N);
  read_sequence(a);
  auto c = berlekamp_massey(a);
  c.pop_back();
  reverse(c.begin(), c.end());
  cout << c.size() << "\n";
  print_sequence(c);
}
