// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
// clang-format on

#include <iostream>
#include <vector>

#include "../../math/combinatorics/lagrange-polynomial-3.hpp"
#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.hpp"

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
  int N, T, M;
  cin >> N >> T >> M;
  vector<mint> ys(N);
  read_sequence(ys);
  NumberTheoreticTransformFriendlyModInt<mint> v;
  auto multiply = [&](const vector<mint>& a, const vector<mint>& b) {
    return v.multiply(a, b);
  };
  print_sequence(lagrange_polynomial(ys, M, T, multiply));
}
