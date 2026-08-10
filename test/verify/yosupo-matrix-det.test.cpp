// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_det
// clang-format on

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/matrix/matrix.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  Matrix<mint> mat(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) cin >> mat[i][j];
  }
  cout << mat.determinant() << endl;
}
