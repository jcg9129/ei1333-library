// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A
// clang-format on

#include <iostream>

#include "../../math/number-theory/prime-factor.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  cout << N << ":";
  for (auto p : prime_factor(N)) {
    while (p.second--) cout << " " << p.first;
  }
  cout << endl;
}
