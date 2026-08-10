// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_I
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/knapsack-limitations-2.hpp"

int main() {
  int N;
  long long W;
  std::cin >> N >> W;
  std::vector<int> v(N);
  std::vector<long long> w(N), m(N);
  for (int i = 0; i < N; i++) {
    std::cin >> v[i] >> w[i] >> m[i];
  }
  std::cout << knapsack_limitations(w, m, v, W) << std::endl;
}
