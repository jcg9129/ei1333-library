// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/discrete_logarithm_mod
// clang-format on

#include <iostream>

#include "../../math/combinatorics/mod-log.hpp"

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    long long X, Y, M;
    cin >> X >> Y >> M;
    cout << mod_log(X, Y, M) << endl;
  }
}
