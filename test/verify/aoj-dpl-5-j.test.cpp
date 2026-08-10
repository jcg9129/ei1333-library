// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J
// clang-format on

#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/combinatorics/partition-table.hpp"

int main() {
  int N, K;
  std::cin >> N >> K;
  std::cout << partition_table<modint1000000007>(N, K)[N][K] << std::endl;
}
