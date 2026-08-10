// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/longest-increasing-subsequence.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int& a : A) cin >> a;
  cout << longest_increasing_subsequence(A, true) << endl;
}
