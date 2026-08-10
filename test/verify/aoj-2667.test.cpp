// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667
// clang-format on

#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

#include "../../graph/tree/heavy-light-decomposition.hpp"

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  HeavyLightDecomposition<> hld(N);
  hld.read(N - 1, 0);
  hld.build();

  struct Query {
    int t, a, b;

    void input() { cin >> t >> a >> b; }
  };

  vector<int> remark;
  vector<Query> qs;
  vector<int64_t> sum(N);

  vector<int> index(N);
  for (int i = 0; i < Q; i++) {
    Query q;
    q.input();
    qs.emplace_back(q);
    if (q.t == 0) {
      remark.emplace_back(q.a);
      remark.emplace_back(q.b);
    } else {
      remark.emplace_back(q.a);
    }
    if (remark.size() >= 2000 || i + 1 == Q) {
      auto es = hld.compress(remark);
      for (int j = 0; j < remark.size(); j++) index[remark[j]] = j;
      vector<int> dist(remark.size()), par(remark.size());
      Graph<> h(remark.size());
      for (auto& p : es) {
        p.first = index[p.first];
        p.second = index[p.second];
        par[p.second] = p.first;
        dist[p.second] = hld.dist(remark[p.first], remark[p.second]);
        h.add_directed_edge(p.first, p.second);
      }
      vector<int64_t> lazy_add(N), backet_add(N);
      for (auto& q : qs) {
        if (q.t == 0) {
          int64_t ret = 0;
          ret += sum[q.a] + sum[q.b] - 2 * sum[hld.lca(q.a, q.b)];
          ret += backet_add[q.a] + backet_add[q.b] -
                 2 * backet_add[hld.lca(q.a, q.b)];
          cout << ret << "\n";
        } else {
          lazy_add[q.a] += q.b;
          q.a = index[q.a];
          function<void(int, int, int64_t)> dfs = [&](int idx, int p,
                                                      int64_t sz) {
            for (auto& to : h.g[idx]) {
              if (to != p) {
                backet_add[remark[to]] += (sz + dist[to]) * q.b;
                dfs(to, idx, sz + dist[to]);
              }
            }
          };
          dfs(q.a, par[q.a], 0);
        }
      }
      function<void(int, int, int64_t, int64_t)> dfs =
          [&](int idx, int par, int64_t add, int64_t all) {
            all += add;
            add += lazy_add[idx];
            sum[idx] += all;
            for (auto& to : hld.g[idx]) {
              if (to != par) dfs(to, idx, add, all);
            }
          };
      dfs(0, -1, 0, 0);
      qs.clear();
      remark.clear();
    }
  }
}
