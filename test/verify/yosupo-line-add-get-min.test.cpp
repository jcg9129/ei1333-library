// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min
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
  const long long MAX_P = 1000000000;
  DynamicLiChaoTree<long long, -MAX_P, MAX_P, kInf> cht;
  for (int i = 0; i < N; i++) {
    long long a, b;
    cin >> a >> b;
    cht.add_line(a, b);
  }
  while (Q--) {
    int T;
    cin >> T;
    if (T == 0) {
      long long A, B;
      cin >> A >> B;
      cht.add_line(A, B);
    } else {
      long long P;
      cin >> P;
      cout << cht.query(P) << "\n";
    }
  }
}
