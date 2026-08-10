// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod
// clang-format on

#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, M;
  cin >> N >> M;
  vector<mint> A(N), B(M);
  for (auto& a : A) cin >> a;
  for (auto& b : B) cin >> b;
  NumberTheoreticTransformFriendlyModInt<mint> ntt;
  for (auto& c : ntt.multiply(A, B)) cout << c << " ";
  cout << endl;
}
