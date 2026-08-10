// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/longest_common_substring
// clang-format on

#include <iostream>
#include <string>

#include "../../string/longest-common-substring.hpp"

using namespace std;

int main() {
  string S, T;
  cin >> S >> T;
  auto [a, b, c, d] = longest_common_substring(S, T);
  cout << a << " " << b << " " << c << " " << d << endl;
}
