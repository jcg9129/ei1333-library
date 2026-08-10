// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_F
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/knapsack-01-2.hpp"

int main() {
  int N, W;
  std::cin >> N >> W;
  std::vector<int> v(N), w(N);
  for (int i = 0; i < N; i++) std::cin >> v[i] >> w[i];
  std::cout << knapsack_01_2(w, v, W) << std::endl;
}
