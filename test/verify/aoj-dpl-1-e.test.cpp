// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E
// clang-format on

#include <iostream>
#include <string>

#include "../../dp/edit-distance.hpp"

int main() {
  std::string S, T;
  std::cin >> S >> T;
  std::cout << edit_distance(S, T) << std::endl;
}
