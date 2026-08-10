#pragma once

#include <algorithm>
#include <string>
#include <vector>

int edit_distance(const std::string& S, const std::string& T) {
  const int N = (int)S.size(), M = (int)T.size();
  std::vector<std::vector<int> > dp(N + 1, std::vector<int>(M + 1, N + M));
  for (int i = 0; i <= N; i++) dp[i][0] = i;
  for (int i = 0; i <= M; i++) dp[0][i] = i;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + 1);
      dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + 1);
      dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + (S[i - 1] != T[j - 1]));
    }
  }
  return dp[N][M];
}
