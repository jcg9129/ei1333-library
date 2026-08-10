// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_sum
// clang-format on

#include <iostream>

#include "../../dp/cumulative-sum.hpp"

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  CumulativeSum<long long> cs(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cs.add(i, x);
  }
  cs.build();
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    cout << cs.fold(l, r) << "\n";
  }
}
