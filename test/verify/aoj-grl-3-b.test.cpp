// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
// clang-format on

#include <algorithm>
#include <iostream>
#include <tuple>

#include "../../graph/others/low-link.hpp"

using namespace std;

int main() {
  int V, E;
  cin >> V >> E;
  LowLink<> g(V);
  g.read(E, 0);
  g.build();
  auto& bridge = g.bridge;
  for (auto& v : bridge) tie(v.from, v.to) = minmax({v.from, v.to});
  sort(bridge.begin(), bridge.end(),
       [](auto& p, auto& q) { return tie(p.from, p.to) < tie(q.from, q.to); });
  for (auto& v : bridge) cout << v.from << " " << v.to << "\n";
}
