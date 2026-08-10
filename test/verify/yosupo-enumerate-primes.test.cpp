// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_primes
// clang-format on

#include <iostream>
#include <vector>

#include "../../math/number-theory/enumerate-primes.hpp"

using namespace std;

int main() {
  int N, A, B;
  cin >> N >> A >> B;
  auto d = enumerate_primes(N);
  vector<int> ans;
  for (int i = B; i < static_cast<int>(d.size()); i += A) {
    ans.emplace_back(d[i]);
  }
  cout << d.size() << " " << ans.size() << "\n";
  for (int i = 0; i < static_cast<int>(ans.size()); i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}
