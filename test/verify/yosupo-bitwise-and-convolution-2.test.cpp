// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_and_convolution
// clang-format on

#include <algorithm>
#include <cstdio>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fft/bitwise-or-convolution.hpp"
#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N;
  in.read(N);
  vector<mint> a(1 << N), b(1 << N);
  for (auto& x : a) {
    int p;
    in.read(p);
    x = p;
  }
  for (auto& x : b) {
    int p;
    in.read(p);
    x = p;
  }
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  auto c = bitwise_or_convolution(a, b);
  reverse(c.begin(), c.end());
  for (int i = 0; i < (1 << N); i++) {
    if (i) out.write(' ');
    out.write(c[i].val());
  }
  out.writeln();
}
