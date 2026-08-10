// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/maximum_independent_set
// clang-format on

#include <iostream>
#include <vector>

#include "../../graph/others/maximum-clique.hpp"

using namespace std;

int main() {
  int V, E;
  cin >> V >> E;
  vector<vector<int>> D(V, vector<int>(V));
  for (int i = 0; i < E; i++) {
    int a, b;
    cin >> a >> b;
    D[a][b] = D[b][a] = true;
  }
  MaximumClique<40> mc(V);
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < i; j++) {
      if (!D[i][j]) mc.add_edge(i, j);
    }
  }
  auto ret = mc.solve();
  cout << ret.size() << "\n";
  for (int i = 0; i < static_cast<int>(ret.size()); i++) {
    if (i > 0) cout << " ";
    cout << ret[i];
  }
  cout << "\n";
}
