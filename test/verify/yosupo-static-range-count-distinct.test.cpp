// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_count_distinct
// clang-format on

#include <iostream>
#include <vector>

#include "../../other/static-range-count-distinct.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto& a : A) cin >> a;
  StaticRangeCountDistinct s(A);
  for (int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    s.add_query(l, r);
  }
  auto ans = s.calclate_queries();
  for (int value : ans) cout << value << "\n";
}
