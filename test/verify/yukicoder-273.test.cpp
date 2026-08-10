// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/273

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../../string/palindromic-tree.hpp"

using namespace std;

int main() {
  string S;
  cin >> S;
  int N = (int)S.size();
  const int negative_infinity = numeric_limits<int>::lowest();
  vector<int> dp1(N + 3, negative_infinity), dp2(N + 1, negative_infinity);
  PalindromicTree t;
  dp2[0] = 1;
  for (int i = 0; i < N; i++) {
    int id = t.add(S[i]);
    auto ret = t.update_dp(
        [&](int id, int pos) {
          if (i + 1 - pos == N)
            dp1[id] = dp2[pos];
          else
            dp1[id] = max(dp2[pos], i + 1 - pos);
        },
        [&](int id, int par) {
          if (t[id].len == N)
            dp1[id] = max(dp1[id], dp1[par]);
          else
            dp1[id] = max(dp1[id], max(dp1[par], t[id].len));
        });
    for (auto& p : ret) dp2[i + 1] = max(dp2[i + 1], dp1[p]);
  }
  cout << dp2[N] << "\n";
}
