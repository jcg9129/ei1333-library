// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest
// clang-format on

#include <iostream>
#include <vector>

#include "../../structure/wavelet/wavelet-matrix.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int& a : A) cin >> a;
  CompressedWaveletMatrix<int, 18> mat(A);
  for (int i = 0; i < Q; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << mat.kth_smallest(a, b, c) << "\n";
  }
}
