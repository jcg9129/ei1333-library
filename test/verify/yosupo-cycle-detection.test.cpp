// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cycle_detection
// clang-format on

#include <iostream>

#include "../../graph/others/cycle-detection.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  CycleDetection<> g(N);
  g.read(M, 0, false, true);
  auto ret = g.build();
  if (ret.empty()) {
    cout << -1 << "\n";
  } else {
    cout << ret.size() << "\n";
    for (auto& e : ret) cout << e.idx << "\n";
  }
}
