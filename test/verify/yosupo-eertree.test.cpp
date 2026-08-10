// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/eertree
// clang-format on

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"
#include "../../string/palindromic-tree.hpp"

using namespace std;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  string S;
  in.read(S);
  PalindromicTree g;
  vector<int> vs;
  vs.reserve(S.size());
  for (auto& c : S) {
    vs.emplace_back(g.add(c) - 1);
  }
  int n = g.size();
  vector<int> p(n), s(n);
  for (int i = 0; i < n; i++) {
    for (auto& e : g[i].link) {
      if (e.second >= 0) p[e.second] = i - 1;
    }
    s[i] = g[i].suffix_link - 1;
  }
  out.writeln(n - 2);
  for (int i = 2; i < n; i++) out.writeln(p[i], s[i]);
  out.writeln(vs);
}
