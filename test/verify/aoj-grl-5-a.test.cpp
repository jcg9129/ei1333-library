// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
// clang-format on

#include <iostream>

#include "../../graph/tree/tree-diameter.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  TreeDiameter<int> g(N);
  g.read(N - 1, 0, true);
  cout << g.build() << endl;
}
