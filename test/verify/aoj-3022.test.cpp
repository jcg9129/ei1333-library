// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3022
// clang-format on

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

#include "../../graph/others/block-cut-tree.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(N);
  for (auto& a : A) cin >> a;
  BlockCutTree<> bct(N);
  bct.read(M);
  bct.build();
  vector<int64_t> weight(bct.tree.size());
  int64_t all = 0;
  for (int i = 0; i < N; i++) {
    weight[bct[i]] += A[i];
    all += A[i];
  }
  vector<int64_t> ans(N, all);
  for (int i = 0; i < N; i++) {
    ans[i] -= A[i];
  }
  function<int64_t(int, int)> rec = [&](int idx, int par) -> int64_t {
    int64_t mx = 0, sum = 0;
    for (auto& to : bct.tree.g[idx]) {
      if (to == par) continue;
      auto res = rec(to, idx);
      sum += res;
      mx = max(mx, res);
    }
    if (idx >= (int)bct.bc.size()) {
      ans[bct.group[idx][0]] = max(all - sum - weight[idx], mx);
    }
    return sum + weight[idx];
  };
  rec(0, -1);
  for (auto& p : ans) cout << p << "\n";
}
