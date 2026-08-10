// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_inversions_query
// clang-format on

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../other/mo.hpp"
#include "../../structure/others/binary-indexed-tree.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto& a : A) cin >> a;
  Mo mo(N, Q);
  for (int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    mo.add_query(l, r);
  }
  vector<int> xs = A;
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  for (auto& a : A) {
    a = lower_bound(xs.begin(), xs.end(), a) - xs.begin();
  }
  BinaryIndexedTree<int> bit(xs.size());
  long long inv = 0, all = 0;
  vector<long long> ans(Q);
  auto add_left = [&](int idx) {
    inv += bit.prod(A[idx]);
    bit.apply(A[idx], 1);
    all++;
  };
  auto add_right = [&](int idx) {
    inv += all - bit.prod(A[idx] + 1);
    bit.apply(A[idx], 1);
    ++all;
  };
  auto erase_left = [&](int idx) {
    inv -= bit.prod(A[idx]);
    bit.apply(A[idx], -1);
    --all;
  };
  auto erase_right = [&](int idx) {
    inv -= all - bit.prod(A[idx] + 1);
    bit.apply(A[idx], -1);
    --all;
  };
  auto query = [&](int idx) { ans[idx] = inv; };
  mo.calclate_queries(add_left, add_right, erase_left, erase_right, query);
  for (auto& p : ans) cout << p << "\n";
}
