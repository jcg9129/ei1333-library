// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
// clang-format on

#include <cstdio>
#include <vector>

#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"
#include "../../structure/others/linear-rmq.hpp"

using namespace std;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  vector<int> A(N);
  in.read(A);
  auto f = [&](int a, int b) { return A[a] < A[b]; };
  auto seg = get_linear_rmq(N, f);
  while (Q--) {
    int l, r;
    in.read(l, r);
    out.writeln(A[seg.fold(l, r)]);
  }
}
