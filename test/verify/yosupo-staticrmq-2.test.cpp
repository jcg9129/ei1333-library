// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
// clang-format on

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../structure/others/disjoint-sparse-table.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int& a : A) cin >> a;
  auto f = [](int a, int b) { return min(a, b); };
  auto st = get_disjoint_sparse_table(A, f);
  while (Q--) {
    int l, r;
    cin >> l >> r;
    cout << st.fold(l, r) << "\n";
  }
}
