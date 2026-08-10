// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primality_test
// clang-format on

#include <iostream>

#include "../../math/number-theory/fast-prime-factorization.hpp"

using namespace std;

int main() {
  int Q;
  cin >> Q;
  while (Q--) {
    long long N;
    cin >> N;
    cout << (FastPrimeFactorization::is_prime(N) ? "Yes" : "No") << "\n";
  }
}
