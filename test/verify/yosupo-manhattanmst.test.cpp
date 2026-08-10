// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/manhattanmst
// clang-format on

#include <iostream>
#include <vector>

#include "../../graph/mst/kruskal.hpp"
#include "../../graph/mst/manhattan-mst.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<long long> X(N), Y(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }
  auto es = manhattan_mst(X, Y);
  auto ret = kruskal(es, N);
  cout << ret.cost << "\n";
  for (auto& e : ret.edges) cout << e.from << " " << e.to << "\n";
}
