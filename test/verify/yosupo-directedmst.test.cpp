// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/directedmst
// clang-format on

#include <iostream>
#include <vector>

#include "../../graph/mst/directed-mst.hpp"

using namespace std;

int main() {
  int n, m, r;
  cin >> n >> m >> r;
  Edges<long long> edges;
  for (int i = 0; i < m; ++i) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    edges.emplace_back(a, b, w);
  }
  auto res = directed_mst(n, r, edges);
  cout << res.cost << "\n";
  vector<int> ans(n);
  ans[r] = r;
  for (auto& e : res.edges) {
    ans[e.to] = e.from;
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}
