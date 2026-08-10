// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_quotients
// clang-format on

#include <iostream>

#include "../../math/number-theory/enumerate-quotients.hpp"

using namespace std;

int main() {
  long long n;
  cin >> n;
  auto quotients = enumerate_quotients(n);
  cout << quotients.size() << endl;
  for (auto&& [q, l, r] : quotients) {
    cout << q << " ";
  }
  cout << endl;
}
