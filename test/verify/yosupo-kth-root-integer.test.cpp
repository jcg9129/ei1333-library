// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_root_integer
// clang-format on

#include <iostream>

#include "../../math/number-theory/kth-root-integer.hpp"

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    unsigned long long a;
    int k;
    cin >> a >> k;
    cout << kth_root_integer(a, k) << "\n";
  }
}
