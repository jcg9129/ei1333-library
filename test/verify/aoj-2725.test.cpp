// competitive-verifier: PROBLEM
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2725

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

#include "../../structure/convex-hull-trick/dynamic-li-chao-tree.hpp"

using namespace std;

constexpr int64_t kInfinity = int64_t{1} << 60;

int main() {
  int N, T;
  cin >> N >> T;
  vector<tuple<int, int, int>> dd;
  dd.reserve(N);
  for (int i = 0; i < N; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a <= T) dd.emplace_back(c, a, b);
  }
  sort(begin(dd), end(dd));
  N = (int)dd.size();
  vector<int64_t> t(N), p(N), f(N);
  for (int i = 0; i < N; i++) {
    tie(f[i], t[i], p[i]) = dd[i];
  }
  vector<vector<int64_t>> dp(N, vector<int64_t>(T + 1, -kInfinity));
  vector<DynamicLiChaoTree<int64_t, 0, 10000, kInfinity>> cht(T + 1);
  for (int i = 0; i < N; i++) {
    dp[i][t[i]] = p[i];
    for (int j = T; j >= t[i]; j--) {
      dp[i][j] = max(dp[i][j], -cht[j - t[i]].query(f[i]) + p[i] - f[i] * f[i]);
    }
    for (int j = T; j >= 0; j--) {
      if (dp[i][j] == -kInfinity) continue;
      cht[j].add_line(-2 * f[i], -(dp[i][j] - f[i] * f[i]));
    }
  }
  int64_t ret = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= T; j++) {
      ret = max(ret, dp[i][j]);
    }
  }
  cout << ret << "\n";
}
