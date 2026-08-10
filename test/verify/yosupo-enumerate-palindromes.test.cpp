// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_palindromes
// clang-format on

#include <iostream>
#include <string>

#include "../../string/manacher.hpp"

using namespace std;

int main() {
  string s;
  cin >> s;
  auto lengths = manacher(s);
  for (int i = 0; i < static_cast<int>(lengths.size()); i++) {
    if (i > 0) cout << " ";
    cout << lengths[i];
  }
  cout << "\n";
}
