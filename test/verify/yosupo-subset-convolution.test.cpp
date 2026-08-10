// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/subset_convolution
// clang-format on

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fft/subset-convolution.hpp"
#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N;
  in.read(N);
  vector<mint> f(1 << N), g(1 << N);
  for (auto& a : f) {
    int x;
    in.read(x);
    a = x;
  }
  for (auto& a : g) {
    int x;
    in.read(x);
    a = x;
  }
  auto h = SubsetConvolution<mint, 20>::multiply(f, g);
  for (auto& a : h) {
    out.write(a.val());
    out.write(' ');
  }
  out.writeln();
}
