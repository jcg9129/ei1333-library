// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
// clang-format on

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "../../structure/bbst/red-black-tree.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int& a : A) cin >> a;
  auto f = [](int a, int b) { return min(a, b); };
  RedBlackTree<int, decltype(f)> rbt(2 * N, f, numeric_limits<int>::max());
  auto root = rbt.build(A);
  while (Q--) {
    int l, r;
    cin >> l >> r;
    cout << rbt.query(root, l, r) << "\n";
  }
}
