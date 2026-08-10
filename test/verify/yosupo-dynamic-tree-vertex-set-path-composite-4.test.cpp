// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
// clang-format on

#include <iostream>
#include <vector>

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../structure/dynamic-tree/dynamic-tree-builder-for-vertex.hpp"
#include "../../structure/dynamic-tree/vertex-set-path-composite.hpp"

using namespace std;

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicTreeBuilderForVertex<LinkCutTree, VertexSetPathComposite<mint> > g(N);
  for (int i = 0; i < N; i++) {
    mint a, b;
    cin >> a >> b;
    g.set_vertex(i, {a, b});
  }
  for (int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  g.build();
  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      g.evert(g.vs[u]);
      g.cut(g.vs[v]);
      g.evert(g.vs[w]);
      g.link(g.vs[w], g.vs[x]);
    } else if (t == 1) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      g.set_key(g.vs[p], {c, d});
    } else {
      int u, v;
      mint x;
      cin >> u >> v >> x;
      auto sum = g.query_path(g.vs[u], g.vs[v]);
      cout << sum.a * x + sum.b << "\n";
    }
  }
}
