// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/montmort_number_mod
// clang-format on

#include <iostream>

#include "../../math/combinatorics/arbitrary-mod-int.hpp"
#include "../../math/combinatorics/montmort.hpp"

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  ArbitraryModInt::set_mod(M);
  auto ret = montmort<ArbitraryModInt>(N);
  ret.erase(ret.begin());
  for (int i = 0; i < static_cast<int>(ret.size()); i++) {
    if (i > 0) cout << " ";
    cout << ret[i];
  }
  cout << endl;
}
