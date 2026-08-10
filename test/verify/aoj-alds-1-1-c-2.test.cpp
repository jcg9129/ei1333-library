// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C
// clang-format on

#include <iostream>

#include "../../math/number-theory/prime-table.hpp"

using namespace std;

int main() {
  auto t = prime_table(100000000);
  int N;
  cin >> N;
  int ret = 0;
  while (N--) {
    int x;
    cin >> x;
    ret += t[x];
  }
  cout << ret << endl;
}
