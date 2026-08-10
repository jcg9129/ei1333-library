// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_rectangle_sum
// clang-format on

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

#include "../../other/dynamic-point-add-rectangle-sum.hpp"
#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"

using namespace std;

int main() {
  int N, Q;
  Scanner in(stdin);
  Printer out(stdout);
  in.read(N, Q);
  DynamicPointAddRectangleSum<int, long long> dpars(N + Q);
  for (int i = 0; i < N; i++) {
    int x, y, z;
    in.read(x, y, z);
    dpars.add_point(x, y, z);
  }
  for (int i = 0; i < Q; i++) {
    int t;
    in.read(t);
    if (t == 0) {
      int x, y, z;
      in.read(x, y, z);
      dpars.add_point(x, y, z);
    } else {
      int l, d, r, u;
      in.read(l, d, r, u);
      dpars.add_query(l, d, r, u);
    }
  }
  for (auto&& ans : dpars.calculate_queries()) {
    out.writeln(ans);
  }
}
