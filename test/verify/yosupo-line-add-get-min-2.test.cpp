// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min
// clang-format on

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp"

using namespace std;

constexpr long long kInf = (1LL << 62) - 1;

int main() {
  int N, Q;
  cin >> N >> Q;
  using CHT = ConvexHullTrickAddMonotone<long long, true>;
  vector<CHT> cht;
  auto add = [&](long long a, long long b) {
    cht.emplace_back();
    cht.back().add(a, b);
    while (cht.size() >= 2 and
           cht.back().H.size() >= cht[cht.size() - 2].H.size()) {
      auto X = cht.back().H;
      cht.pop_back();
      auto Y = cht.back().H;
      cht.pop_back();
      reverse(X.begin(), X.end());
      reverse(Y.begin(), Y.end());
      CHT c;
      int k = 0;
      for (auto& p : X) {
        while (k < (int)Y.size() and Y[k] < p) {
          c.add(Y[k].first, Y[k].second);
          ++k;
        }
        c.add(p.first, p.second);
      }
      while (k < (int)Y.size()) {
        c.add(Y[k].first, Y[k].second);
        ++k;
      }
      cht.emplace_back(c);
    }
  };
  for (int i = 0; i < N; i++) {
    long long a, b;
    cin >> a >> b;
    add(a, b);
  }
  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      long long a, b;
      cin >> a >> b;
      add(a, b);
    } else {
      long long x;
      cin >> x;
      long long ret = kInf;
      for (auto& c : cht) {
        ret = min(ret, c.query(x));
      }
      cout << ret << "\n";
    }
  }
}
