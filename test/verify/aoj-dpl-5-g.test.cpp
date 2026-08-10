// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G
// clang-format on

#include <iostream>

#include "../../math/combinatorics/bell-number.hpp"
#include "../../math/combinatorics/montgomery-mod-int.hpp"

int main() {
  int N, K;
  std::cin >> N >> K;
  std::cout << bell_number<modint1000000007>(N, K) << std::endl;
}
