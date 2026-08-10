// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_frequency
// clang-format on

#include <iostream>
#include <vector>

#include "../../other/static-range-frequency.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto& a : A) cin >> a;
  StaticRangeFrequency s(A);
  while (Q--) {
    int l, r, x;
    cin >> l >> r >> x;
    cout << s.query(l, r, x) << "\n";
  }
}
