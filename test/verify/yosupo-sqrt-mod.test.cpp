// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_mod
// clang-format on

#include <iostream>

#include "../../math/combinatorics/mod-pow.hpp"
#include "../../math/combinatorics/mod-sqrt.hpp"

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    long long Y, P;
    cin >> Y >> P;
    cout << mod_sqrt(Y, P) << endl;
  }
}
