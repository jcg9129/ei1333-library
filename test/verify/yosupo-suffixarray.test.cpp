// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/suffixarray
// clang-format on

#include <iostream>
#include <string>

#include "../../string/suffix-array.hpp"

using namespace std;

int main() {
  string s;
  cin >> s;
  auto sa = SuffixArray(s);
  sa.erase(sa.begin());
  for (int i = 0; i < static_cast<int>(sa.size()); i++) {
    if (i > 0) cout << " ";
    cout << sa[i];
  }
  cout << "\n";
}
