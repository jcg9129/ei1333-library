// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bipartite_edge_coloring
// clang-format on

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../graph/others/bipartite-graph-edge-coloring.hpp"

using namespace std;

int main() {
  int L, R, M;
  cin >> L >> R >> M;
  BipariteGraphEdgeColoring ecbg;
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    ecbg.add_edge(a, b);
  }
  auto res = ecbg.build();
  cout << res.size() << "\n";
  vector<int> color(M);
  for (int i = 0; i < res.size(); i++) {
    for (auto& j : res[i]) color[j] = i;
  }
  for (auto& c : color) cout << c << "\n";
}
