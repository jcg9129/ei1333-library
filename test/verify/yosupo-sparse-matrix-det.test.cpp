// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sparse_matrix_det
// clang-format on

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/berlekamp-massey.hpp"
#include "../../math/fps/formal-power-series.hpp"
#include "../../math/fps/sparse-matrix.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, K;
  cin >> N >> K;
  FPSGraph<mint> g(N);
  for (int i = 0; i < K; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].emplace_back(b, c);
  }
  cout << sparse_determinant(g) << endl;
}
