// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/factorize
// clang-format on

#include <algorithm>
#include <iostream>

#include "../../math/number-theory/fast-prime-factorization.hpp"

using namespace std;

int main() {
  int Q;
  cin >> Q;
  while (Q--) {
    long long X;
    cin >> X;
    auto ret = FastPrimeFactorization::prime_factor(X);
    sort(ret.begin(), ret.end());
    cout << ret.size();
    for (auto factor : ret) cout << " " << factor;
    cout << "\n";
  }
}
