// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/general_matching
// clang-format on

#include <iostream>

#include "../../graph/flow/gabow-edmonds.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  GabowEdmonds flow(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    flow.add_edge(a, b);
  }
  auto ret = flow.max_matching();
  cout << ret.size() << endl;
  for (auto& p : ret) cout << p.first << " " << p.second << endl;
}
