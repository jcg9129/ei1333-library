// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_edge_connected_components
// clang-format on

#include <iostream>

#include "../../graph/connected-components/two-edge-connected-components.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  TwoEdgeConnectedComponents<> g(N);
  g.read(M, 0);
  g.build();
  cout << g.group.size() << "\n";
  for (auto& p : g.group) {
    cout << p.size();
    for (int v : p) cout << " " << v;
    cout << "\n";
  }
}
