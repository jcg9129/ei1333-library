// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_and_convolution
// clang-format on

#include <cstdio>
#include <vector>

#include "../../math/fft/superset-zeta-moebius-transform-simd.hpp"
#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"

using namespace std;

const int MOD = 998244353;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N;
  in.read(N);
  int a[1 << N], b[1 << N];
  for (int i = 0; i < (1 << N); i++) in.read(a[i]);
  for (int i = 0; i < (1 << N); i++) in.read(b[i]);
  bitwise_and_convolution_simd<MOD>(a, b, 1 << N);
  for (int i = 0; i < (1 << N); i++) {
    if (i) out.write(' ');
    out.write(a[i]);
  }
  out.writeln();
}
