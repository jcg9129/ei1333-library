// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B
// clang-format on

#include <iostream>

#include "../../math/combinatorics/mod-pow.hpp"

using namespace std;

int main() {
  long long M, N;
  cin >> M >> N;
  cout << mod_pow(M, N, 1000000007LL) << endl;
}
