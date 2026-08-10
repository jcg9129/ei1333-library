// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D
// clang-format on

#include <iostream>

#include "../../math/number-theory/euler-phi.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  cout << euler_phi<long long>(N) << endl;
}
