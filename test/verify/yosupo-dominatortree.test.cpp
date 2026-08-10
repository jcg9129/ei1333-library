// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dominatortree
// clang-format on

#include <iostream>

#include "../../graph/others/dominator-tree.hpp"

using namespace std;

int main() {
  int N, M, S;
  cin >> N >> M >> S;
  DominatorTree<> g(N);
  g.read(M, 0, false, true);
  g.build(S);
  for (int i = 0; i < N; i++) cout << g[i] << " ";
  cout << endl;
}
