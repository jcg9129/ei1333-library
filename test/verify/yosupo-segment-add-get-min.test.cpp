// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min
// clang-format on

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../structure/convex-hull-trick/dynamic-li-chao-tree.hpp"

using namespace std;

constexpr long long kInf = (1LL << 62) - 1;

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicLiChaoTree<long long, -1000000000, 1000000000, kInf> dlct;
  for (int i = 0; i < N; i++) {
    long long l, r, a, b;
    cin >> l >> r >> a >> b;
    dlct.add_segment(l, r, a, b);
  }
  for (int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if (t == 0) {
      long long l, r, a, b;
      cin >> l >> r >> a >> b;
      dlct.add_segment(l, r, a, b);
    } else {
      long long p;
      cin >> p;
      auto ret = dlct.query(p);
      if (ret >= kInf)
        cout << "INFINITY\n";
      else
        cout << ret << endl;
    }
  }
}
