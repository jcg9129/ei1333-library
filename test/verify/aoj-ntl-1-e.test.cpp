// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E
// clang-format on

#include <iostream>

#include "../../math/number-theory/extgcd.hpp"

using namespace std;

int main() {
  int a, b, x, y;
  cin >> a >> b;
  extgcd(a, b, x, y);
  cout << x << " " << y << endl;
}
