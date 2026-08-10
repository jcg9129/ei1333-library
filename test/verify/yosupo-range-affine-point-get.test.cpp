// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_point_get
// clang-format on

#include <iostream>
#include <utility>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../structure/class/affine.hpp"
#include "../../structure/segment-tree/dual-segment-tree.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto& a : A) cin >> a;

  using pi = Affine<mint>;
  auto h = [](const pi& a, const pi& b) -> pi { return pi::op(a, b); };
  auto id = []() -> pi { return {1, 0}; };
  DualSegmentTree seg(LambdaAct(h, id), N);
  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, {b, c});
    } else {
      int i;
      cin >> i;
      cout << seg[i].eval(A[i]).val() << "\n";
    }
  }
}
