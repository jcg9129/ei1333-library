// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/952

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp"

using namespace std;

constexpr int64_t kInfinity = int64_t{1} << 60;

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (auto& a : A) cin >> a;
  vector<int64_t> S(N + 2);
  for (int i = 0; i < N; i++) {
    S[i + 1] = S[i] + A[i];
  }

  vector<vector<int64_t>> dp(N + 2, vector<int64_t>(N + 1, kInfinity));
  vector<vector<int64_t>> dp2(N + 2, vector<int64_t>(N + 1, kInfinity));
  dp[0][0] = 0;

  vector<ConvexHullTrickAddMonotone<int64_t, true>> chts(2 * N + 10);
  const int Shift = N + 5;

  for (int i = 0; i <= N + 1; i++) {
    if (i <= N) {
      for (int j = 0; j <= N; j++) {
        int Q = j - i + Shift;
        if (!chts[Q].empty())
          dp2[i + 1][j] =
              min(dp2[i + 1][j],
                  S[i] * S[i] + chts[Q].query_monotone_dec(-2 * S[i]));
      }
    }
    for (int j = 0; j <= N; j++) {
      if (i) dp[i][j] = min(dp[i - 1][j], dp2[i][j]);
      if (dp[i][j] != kInfinity)
        chts[j - i + Shift].add(S[i], dp[i][j] + S[i] * S[i]);
    }
  }

  for (int i = 1; i <= N; i++) {
    cout << dp[N + 1][i] << endl;
  }
}
