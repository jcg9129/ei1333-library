// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind
// clang-format on

#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/stirling-first.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  auto ans = stirling_first<FPS, mint>(N);
  for (int i = 0; i < static_cast<int>(ans.size()); i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << endl;
}
