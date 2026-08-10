// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/wildcard_pattern_matching
// clang-format on

#include <iostream>
#include <string>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../string/wildcard-pattern-matching.hpp"

using namespace std;

int main() {
  string S, T;
  cin >> S >> T;
  for (auto& a : wildcard_pattern_matching<modint998244353>(S, T, '*')) {
    cout << a;
  }
  cout << endl;
}
