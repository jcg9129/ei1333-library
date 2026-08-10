// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C
// clang-format on

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../dp/knapsack.hpp"

using namespace std;

int main() {
  int N, W;
  cin >> N >> W;
  vector<int> v(N), w(N);
  for (int i = 0; i < N; i++) cin >> v[i] >> w[i];
  auto ret = knapsack(w, v, W, -1);
  cout << *max_element(ret.begin(), ret.end()) << endl;
}
