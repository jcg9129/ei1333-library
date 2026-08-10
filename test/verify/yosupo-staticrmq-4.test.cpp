// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
// clang-format on

#include <iostream>
#include <vector>

#include "../../graph/others/cartesian-tree.hpp"
#include "../../graph/tree/pmormq-lowest-common-ancestor.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int& a : A) cin >> a;
  auto t = cartesian_tree(A);
  PMORMQLowestCommonAncestor<int> g(N);
  int root = -1;
  for (int i = 0; i < N; i++) {
    if (t[i] == -1) {
      root = i;
      continue;
    }
    g.add_directed_edge(t[i], i);
  }
  g.build(root);
  while (Q--) {
    int l, r;
    cin >> l >> r;
    cout << A[g.lca(l, r - 1)] << "\n";
  }
}
