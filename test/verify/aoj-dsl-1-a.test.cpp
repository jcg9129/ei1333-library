// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A
// clang-format on

#include <cstdio>

#include "../../structure/union-find/union-find.hpp"

int main() {
  int N, Q;
  std::scanf("%d %d", &N, &Q);
  UnionFind uf(N);
  while (Q--) {
    int t, x, y;
    std::scanf("%d %d %d", &t, &x, &y);
    if (t == 0)
      uf.unite(x, y);
    else
      std::printf("%d\n", uf.find(x) == uf.find(y));
  }
}
