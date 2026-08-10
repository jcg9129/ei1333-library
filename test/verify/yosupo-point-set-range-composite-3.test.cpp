// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite
// clang-format on

#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../structure/class/point-set-range-composite.hpp"
#include "../../structure/segment-tree/segment-tree.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<Affine<mint> > data(N);
  for (auto& d : data) {
    mint x, y;
    cin >> x >> y;
    d = {x, y};
  }
  auto seg = SegmentTree(PointSetRangeComposite<mint>(), data);
  for (int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if (t == 0) {
      int p;
      mint a, b;
      cin >> p >> a >> b;
      seg.set(p, {a, b});
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      cout << seg.prod(l, r).eval(x) << "\n";
    }
  }
}
