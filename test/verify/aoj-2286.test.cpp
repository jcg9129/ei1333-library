// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2286
// clang-format on

#include <cstdint>
#include <iostream>
#include <vector>

#include "../../math/number-theory/euler-phi-table.hpp"

using namespace std;

int main() {
  const int MAX_N = 1000000;
  auto phi = euler_phi_table(MAX_N);
  vector<int64_t> S(MAX_N + 1);
  S[1] = 2;
  for (int i = 2; i <= MAX_N; i++) {
    S[i] = S[i - 1] + phi[i];
  }
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    cout << S[N] << "\n";
  }
}
