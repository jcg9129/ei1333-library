// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences

#include "../../template/template.hpp"

#include "../../math/combinatorics/count-bounded-increasing-sequences.hpp"
#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../other/scanner.hpp"

using mint = modint998244353;

int main() {
  Scanner input(stdin);
  int N, M;
  input.read(N, M);
  vector< int > A(N), B(N);
  input.read(A, B);
  cout << count_bounded_increasing_sequences< mint >(A, B).val() << endl;
}
