// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/maximum_independent_set
// clang-format on

#include <iostream>

#include "../../graph/others/maximum-independent-set.hpp"
#include "../../math/matrix/matrix.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  Matrix<bool> mat(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    mat[a][b] = true;
    mat[b][a] = true;
  }
  auto ret = maximum_independent_set(mat);
  cout << ret.size() << endl;
  for (int i = 0; i < static_cast<int>(ret.size()); i++) {
    if (i > 0) cout << " ";
    cout << ret[i];
  }
  cout << endl;
}
