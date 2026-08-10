// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/largest-rectangle.hpp"

int main() {
  int N;
  std::cin >> N;
  std::vector<int> h(N);
  for (int& height : h) std::cin >> height;
  std::cout << largest_rectangle(h) << std::endl;
}
