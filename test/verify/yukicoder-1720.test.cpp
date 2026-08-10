// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1720

#include <functional>
#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../structure/others/permutation-tree.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, K;
  cin >> N >> K;
  vector<int> A(N);
  for (auto& a : A) cin >> a;
  for (auto& a : A) --a;
  using NP = PermutationTree::Node*;
  vector<vector<mint>> dp(K + 1, vector<mint>(N + 1));
  dp[0][0] = 1;
  function<void(NP)> rec = [&](NP r) {
    if (r->is_cut() or r->is_leaf()) {
      for (int k = 0; k < K; k++) {
        dp[k + 1][r->r] += dp[k][r->l];
      }
    }
    vector<mint> sum(K);
    for (auto& c : r->ch) {
      rec(c);
      if (r->is_join()) {
        for (int k = 0; k < K; k++) {
          dp[k + 1][c->r] += sum[k];
          sum[k] += dp[k][c->l];
        }
      }
    }
  };
  rec(PermutationTree::build(A));
  for (int i = 1; i <= K; i++) {
    cout << dp[i][N] << "\n";
  }
}
