// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convex_layers
// clang-format on

#include <iostream>
#include <utility>
#include <vector>

#include "../../geometry/convex-layers.hpp"

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> ps(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }
  auto layers = convex_layers<int, long long>(ps);
  for (int i = 0; i < static_cast<int>(layers.size()); i++) {
    if (i > 0) cout << " ";
    cout << layers[i];
  }
  cout << "\n";
}
