// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
// clang-format on

#include <iostream>

#include "../../graph/connected-components/strongly-connected-components.hpp"

using namespace std;

int main() {
  int V, E, Q;
  cin >> V >> E;
  StronglyConnectedComponents<> scc(V);
  scc.read(E, false, 0, true);
  scc.build();
  cin >> Q;
  while (Q--) {
    int a, b;
    cin >> a >> b;
    cout << static_cast<int>(scc[a] == scc[b]) << "\n";
  }
}
