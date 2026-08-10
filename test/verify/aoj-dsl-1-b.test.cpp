// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
// clang-format on

#include <iostream>

#include "../../structure/union-find/weighted-union-find.hpp"

int main() {
  int N, M;
  std::cin >> N >> M;
  WeightedUnionFind<int> tree(N);
  while (M--) {
    int A, B, C, D;
    std::cin >> A >> B >> C;
    if (A == 0) {
      std::cin >> D;
      tree.unite(B, C, D);
    } else {
      if (tree.find(B) == tree.find(C)) {
        std::cout << tree.diff(B, C) << std::endl;
      } else {
        std::cout << "?" << std::endl;
      }
    }
  }
}
