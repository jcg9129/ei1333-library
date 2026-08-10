// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2603
// clang-format on

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "../../dp/divide-and-conquer-optimization.hpp"

using namespace std;

int main() {
  int S, N, M;
  cin >> S >> N >> M;
  vector<int> X(S);
  for (auto& x : X) cin >> x;
  vector<int> T(N);
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    T[i] = a - X[--b];
  }
  sort(begin(T), end(T));
  vector<vector<int>> mat(N, vector<int>(N));
  for (int right = N - 1; right >= 0; right--) {
    for (int left = right - 1; left >= 0; left--) {
      mat[left][right] = mat[left + 1][right] + T[right] - T[left];
    }
  }
  const int infinity = numeric_limits<int>::max();
  auto val = divide_and_conquer_optimization<int>(
      M, N, infinity, [&](int a, int b) { return mat[a][b - 1]; });
  int ret = infinity;
  for (int k = 0; k < static_cast<int>(val.size()); k++)
    ret = min(ret, val[k].back());
  cout << ret << "\n";
}
