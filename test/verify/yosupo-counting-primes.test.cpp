// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/counting_primes
// clang-format on

#include <iostream>

#include "../../math/number-theory/prime-count.hpp"

using namespace std;

int main() {
  long long n;
  cin >> n;
  PrimeCount<> pc;
  cout << pc.pi(n) << "\n";
}
