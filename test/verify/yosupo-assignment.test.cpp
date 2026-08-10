// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/assignment
// clang-format on

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../graph/flow/hungarian.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  Matrix<long long> X(N + 1, N + 1);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> X[j][i];
    }
  }
  auto ret = hungarian(X);
  cout << ret.first << "\n";
  ret.second.erase(ret.second.begin());
  for (auto& p : ret.second) --p;
  for (int i = 0; i < static_cast<int>(ret.second.size()); i++) {
    if (i > 0) cout << " ";
    cout << ret.second[i];
  }
  cout << "\n";
}
