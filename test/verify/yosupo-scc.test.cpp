// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/scc
// clang-format on

#include <iostream>

#include "../../graph/connected-components/strongly-connected-components.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  StronglyConnectedComponents<> g(N);
  g.read(M, 0, false, true);
  g.build();
  cout << g.group.size() << "\n";
  for (auto& p : g.group) {
    cout << p.size();
    for (int v : p) cout << " " << v;
    cout << "\n";
  }
}
