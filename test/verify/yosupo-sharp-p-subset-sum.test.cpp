// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sharp_p_subset_sum
// clang-format on

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/count-subset-sum.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, T;
  cin >> N >> T;
  vector<mint> c(T + 1);
  for (int i = 0; i < N; i++) {
    int s;
    cin >> s;
    c[s] += 1;
  }
  auto ret = count_subset_sum<FPS>(c);
  ret.erase(ret.begin());
  for (int i = 0; i < static_cast<int>(ret.size()); i++) {
    if (i > 0) cout << " ";
    cout << ret[i];
  }
  cout << "\n";
}
