// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_linear_add_range_min
// clang-format on

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../structure/segment-tree/range-linear-add-range-min-segment-tree.hpp"

using namespace std;

constexpr long long kInf = (1LL << 62) - 1;

int main() {
  int n, q;
  cin >> n >> q;
  vector<long long> as(n);
  for (auto& a : as) cin >> a;
  RangeLinearAddRangeMinSegmentTree<long long, long long, __int128_t> seg(as,
                                                                          kInf);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      seg.apply(l, r, b, c);
    } else {
      cout << seg.prod(l, r) << "\n";
    }
  }
}
