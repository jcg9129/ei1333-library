// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
// clang-format on

#include <iostream>

#include "../../structure/others/binary-indexed-tree.hpp"

int main() {
  int N, Q;
  std::cin >> N >> Q;
  BinaryIndexedTree<int> bit(N);
  while (Q--) {
    int T, X, Y;
    std::cin >> T >> X >> Y;
    if (T == 0)
      bit.apply(X - 1, Y);
    else
      std::cout << bit.prod(X - 1, Y) << "\n";
  }
}
