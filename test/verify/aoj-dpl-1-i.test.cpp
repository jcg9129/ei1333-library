// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_I
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/knapsack-limitations-2.hpp"

using namespace std;

int main() {
  int N;
  long long W;
  cin >> N >> W;
  vector<int> v(N);
  vector<long long> w(N), m(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i] >> w[i] >> m[i];
  }
  cout << knapsack_limitations(w, m, v, W) << endl;
}
