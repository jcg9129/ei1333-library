// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sum_of_floor_of_linear
// clang-format on

#include <iostream>

#include "../../math/number-theory/sum-of-floor-of-linear.hpp"

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    long long N, M, A, B;
    cin >> N >> M >> A >> B;
    cout << sum_of_floor_of_linear(N, M, A, B) << "\n";
  }
}
