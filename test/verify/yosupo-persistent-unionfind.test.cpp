// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_unionfind
// clang-format on

#include <iostream>
#include <vector>

#include "../../structure/union-find/persistent-union-find.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<PersistentUnionFind> uf(Q + 1);
  uf[0] = PersistentUnionFind(N);
  for (int i = 1; i <= Q; i++) {
    int t, k, u, v;
    cin >> t >> k >> u >> v;
    ++k;
    if (t == 0) {
      uf[i] = uf[k];
      uf[i].unite(u, v);
    } else {
      cout << (uf[k].find(u) == uf[k].find(v)) << "\n";
    }
  }
}
