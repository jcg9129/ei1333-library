// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
// clang-format on

#include <algorithm>
#include <climits>
#include <iostream>

#include "../../structure/segment-tree/segment-tree.hpp"

int main() {
  int N, Q;
  std::cin >> N >> Q;
  auto seg =
      SegmentTree(LambdaMonoid([](int a, int b) { return std::min(a, b); },
                               []() { return INT_MAX; }),
                  N);
  while (Q--) {
    int T, X, Y;
    std::cin >> T >> X >> Y;
    if (T == 0)
      seg.set(X, Y);
    else
      std::cout << seg.prod(X, Y + 1) << "\n";
  }
}
