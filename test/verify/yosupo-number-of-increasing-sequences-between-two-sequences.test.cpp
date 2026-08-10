// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences
// clang-format on

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../../math/combinatorics/count-bounded-increasing-sequences.hpp"
#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../other/scanner.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  Scanner input(stdin);
  int N, M;
  input.read(N, M);
  vector<int> A(N), B(N);
  input.read(A, B);
  cout << count_bounded_increasing_sequences<mint>(A, B).val() << endl;
}
