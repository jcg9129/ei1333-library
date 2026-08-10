// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/zalgorithm
// clang-format on

#include <iostream>
#include <string>

#include "../../string/z-algorithm.hpp"

using namespace std;

int main() {
  string s;
  cin >> s;
  auto z = ZAlgorithm(s).get();
  for (int i = 0; i < static_cast<int>(z.size()); i++) {
    if (i > 0) cout << " ";
    cout << z[i];
  }
  cout << "\n";
}
