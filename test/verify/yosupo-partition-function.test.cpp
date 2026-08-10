// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/partition_function
// clang-format on

#include <iostream>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/partition.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  auto ans = partition<FPS, mint>(N);
  for (int i = 0; i < static_cast<int>(ans.size()); i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << endl;
}
