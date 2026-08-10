// competitive-verifier: PROBLEM
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2674

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../structure/segment-tree/segment-tree-fractional-cascading.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N;
  vector<int64_t> X(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i];
  }
  SegmentTreeFractionalCascading seg(X);
  cin >> Q;
  while (Q--) {
    int L, R, E;
    cin >> L >> R >> E;
    --L, --R;
    cout << (R - L + 1) -
                seg.prod(L, R + 1, min(X[L], X[R]) - E, max(X[L], X[R]) + E + 1)
         << "\n";
  }
}
