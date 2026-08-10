// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tetration_mod
// clang-format on

#include <iostream>

#include "../../math/combinatorics/mod-tetration.hpp"

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int a, b, m;
    cin >> a >> b >> m;
    cout << mod_tetration<long long>(a, b, m) % m << "\n";
  }
}
