// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tree_diameter
// clang-format on

#include <iostream>

#include "../../graph/tree/tree-diameter.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  TreeDiameter<long long> g(N);
  g.read(N - 1, 0, true);
  cout << g.build() << " ";
  cout << g.path.size() + 1 << "\n";
  cout << g.path[0].from;
  for (auto& edge : g.path) cout << " " << edge.to;
  cout << "\n";
}
