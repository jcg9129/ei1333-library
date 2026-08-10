// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/longest-increasing-subsequence.hpp"

int main() {
  int N;
  std::cin >> N;
  std::vector<int> A(N);
  for (int& a : A) std::cin >> a;
  std::cout << longest_increasing_subsequence(A, true) << std::endl;
}
