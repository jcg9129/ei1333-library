// clang-format off
// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450
// clang-format on

#include <algorithm>
#include <iostream>
#include <limits>

#include "../../structure/dynamic-tree/dynamic-tree-builder-for-vertex.hpp"
#include "../../structure/dynamic-tree/lazy-link-cut-tree.hpp"

using namespace std;

constexpr int kInfinity = numeric_limits<int>::max();

struct TreeDPInfo {
  struct Lazy {
    int v;

    static constexpr Lazy id() { return {kInfinity}; }

    void propagate(const Lazy& p) {
      if (p.v != kInfinity) v = p.v;
    }
  };

  struct Path {
    int ans, all, suf, pref, sz;

    void propagate(const Lazy& p) {
      if (p.v != kInfinity) {
        all = p.v * sz;
        ans = suf = pref = max(p.v, all);
      }
    }
  };

  struct Info {
    int v;

    void propagate(const Lazy& p) {
      if (p.v != kInfinity) v = p.v;
    }
  };

  static Path vertex(const Info& u) { return {u.v, u.v, u.v, u.v, 1}; }

  static Path compress(const Path& p, const Path& c) {
    return {max({p.ans, c.ans, p.suf + c.pref}), p.all + c.all,
            max(c.suf, p.suf + c.all), max(p.pref, c.pref + p.all),
            p.sz + c.sz};
  }
};

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicTreeBuilderForVertex<LazyLinkCutTree, TreeDPInfo> g(N);
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    g.set_vertex(i, {x});
  }
  for (int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g.add_edge(a, b);
  }
  g.build();
  while (Q--) {
    int t, a, b, c;
    cin >> t >> a >> b >> c;
    --a, --b;
    if (t == 2) {
      cout << g.query_path(g.vs[a], g.vs[b]).ans << "\n";
    } else {
      g.set_propagate_path(g.vs[a], g.vs[b], {c});
    }
  }
}
