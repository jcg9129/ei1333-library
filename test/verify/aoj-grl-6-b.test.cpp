// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
// clang-format on

#include <cstdio>

#include "../../graph/flow/primal-dual.hpp"

using namespace std;

int main() {
  int V, E, F;
  scanf("%d %d %d", &V, &E, &F);
  PrimalDual<int, int> g(V);
  for (int i = 0; i < E; i++) {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    g.add_edge(a, b, c, d);
  }
  printf("%d\n", g.min_cost_flow(0, V - 1, F));
}
