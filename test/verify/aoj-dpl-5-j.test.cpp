// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J
// clang-format on

#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/combinatorics/partition-table.hpp"

using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  cout << partition_table<modint1000000007>(N, K)[N][K] << endl;
}
