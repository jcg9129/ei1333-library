// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
// clang-format on

#include <iostream>

#include "../../graph/tree/rmq-lowest-common-ancestor.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N;
  RMQLowestCommonAncestor<int> lca(N);
  for (int i = 0; i < N; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int c;
      cin >> c;
      lca.add_edge(i, c);
    }
  }
  lca.build();
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    int u, v;
    cin >> u >> v;
    cout << lca.lca(u, v) << "\n";
  }
}
