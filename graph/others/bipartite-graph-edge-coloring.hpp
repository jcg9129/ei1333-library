#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <utility>
#include <valarray>
#include <vector>

#include "../../structure/union-find/union-find.hpp"
#include "../flow/bipartite-flow.hpp"
#include "eulerian-trail.hpp"

/**
 * @brief Bipartite Graph Edge Coloring(二部グラフの辺彩色)
 *
 * @see https://ei1333.hateblo.jp/entry/2020/08/25/015955
 */
struct BipariteGraphEdgeColoring {
 private:
  std::vector<std::vector<int> > ans;
  std::vector<int> A, B;
  int L, R;

  struct RegularGraph {
    int k{}, n{};
    std::vector<int> A, B;
  };
  RegularGraph g;

  static UnionFind contract(std::valarray<int>& deg, int k) {
    using pi = std::pair<int, int>;
    std::priority_queue<pi, std::vector<pi>, std::greater<> > que;
    for (int i = 0; i < (int)deg.size(); i++) {
      que.emplace(deg[i], i);
    }
    UnionFind uf(deg.size());
    while (que.size() > 1) {
      auto p = que.top();
      que.pop();
      auto q = que.top();
      que.pop();
      if (p.first + q.first > k) continue;
      p.first += q.first;
      uf.unite(p.second, q.second);
      que.emplace(p);
    }
    return uf;
  }

  RegularGraph build_k_regular_graph() {
    std::valarray<int> deg[2];
    deg[0] = std::valarray<int>(L);
    deg[1] = std::valarray<int>(R);
    for (auto& p : A) deg[0][p]++;
    for (auto& p : B) deg[1][p]++;

    int k = std::max(deg[0].max(), deg[1].max());

    /* step 1 */
    UnionFind uf[2];
    uf[0] = contract(deg[0], k);
    uf[1] = contract(deg[1], k);

    std::vector<int> id[2];
    int ptr[] = {0, 0};
    id[0] = std::vector<int>(L);
    id[1] = std::vector<int>(R);
    for (int i = 0; i < L; i++)
      if (uf[0].find(i) == i) id[0][i] = ptr[0]++;
    for (int i = 0; i < R; i++)
      if (uf[1].find(i) == i) id[1][i] = ptr[1]++;

    /* step 2 */
    int N = std::max(ptr[0], ptr[1]);
    deg[0] = std::valarray<int>(N);
    deg[1] = std::valarray<int>(N);

    /* step 3 */
    std::vector<int> C, D;
    C.reserve(N * k);
    D.reserve(N * k);
    for (int i = 0; i < (int)A.size(); i++) {
      int u = id[0][uf[0].find(A[i])];
      int v = id[1][uf[1].find(B[i])];
      C.emplace_back(u);
      D.emplace_back(v);
      deg[0][u]++;
      deg[1][v]++;
    }
    int j = 0;
    for (int i = 0; i < N; i++) {
      while (deg[0][i] < k) {
        while (deg[1][j] == k) ++j;
        C.emplace_back(i);
        D.emplace_back(j);
        ++deg[0][i];
        ++deg[1][j];
      }
    }

    return {k, N, C, D};
  }

  void rec(const std::vector<int>& ord, int k) {
    if (k == 0) {
      return;
    } else if (k == 1) {
      ans.emplace_back(ord);
      return;
    } else if ((k & 1) == 0) {
      EulerianTrail<false> et(g.n + g.n);
      for (auto& p : ord) et.add_edge(g.A[p], g.B[p] + g.n);
      auto paths = et.enumerate_eulerian_trail();
      std::vector<int> path;
      for (auto& ps : paths) {
        for (auto& e : ps) path.emplace_back(ord[e]);
      }
      std::vector<int> beet[2];
      for (int i = 0; i < (int)path.size(); i++) {
        beet[i & 1].emplace_back(path[i]);
      }
      rec(beet[0], k / 2);
      rec(beet[1], k / 2);
    } else {
      BipartiteFlow flow(g.n, g.n);
      for (auto& i : ord) flow.add_edge(g.A[i], g.B[i]);
      flow.max_matching();
      std::vector<int> beet;
      ans.emplace_back();
      for (auto& i : ord) {
        if (flow.match_l[g.A[i]] == g.B[i]) {
          flow.match_l[g.A[i]] = -1;
          ans.back().emplace_back(i);
        } else {
          beet.emplace_back(i);
        }
      }
      rec(beet, k - 1);
    }
  }

 public:
  explicit BipariteGraphEdgeColoring() : L(0), R(0) {}

  void add_edge(int a, int b) {
    A.emplace_back(a);
    B.emplace_back(b);
    L = std::max(L, a + 1);
    R = std::max(R, b + 1);
  }

  std::vector<std::vector<int> > build() {
    g = build_k_regular_graph();
    std::vector<int> ord(g.A.size());
    std::iota(ord.begin(), ord.end(), 0);
    rec(ord, g.k);
    std::vector<std::vector<int> > res;
    for (int i = 0; i < (int)ans.size(); i++) {
      res.emplace_back();
      for (auto& j : ans[i])
        if (j < (int)A.size()) res.back().emplace_back(j);
    }
    return res;
  }
};
