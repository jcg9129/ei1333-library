#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

/**
 * @brief Bipartite Flow(二部グラフのフロー)
 *
 */
struct BipartiteFlow {
  std::size_t n, m, time_stamp;
  std::vector<std::vector<int> > g, rg;
  std::vector<int> match_l, match_r, dist, used, alive;
  bool matched;

 public:
  explicit BipartiteFlow(std::size_t n, std::size_t m)
      : n(n),
        m(m),
        time_stamp(0),
        g(n),
        rg(m),
        match_l(n, -1),
        match_r(m, -1),
        used(n),
        alive(n, 1),
        matched(false) {}

  void add_edge(int u, int v) {
    g[u].push_back(v);
    rg[v].emplace_back(u);
  }

  std::vector<std::pair<int, int> > max_matching() {
    matched = true;
    for (;;) {
      build_augment_path();
      ++time_stamp;
      int flow = 0;
      for (int i = 0; i < (int)n; i++) {
        if (match_l[i] == -1) flow += find_min_dist_augment_path(i);
      }
      if (flow == 0) break;
    }
    std::vector<std::pair<int, int> > ret;
    for (int i = 0; i < (int)n; i++) {
      if (match_l[i] >= 0) ret.emplace_back(i, match_l[i]);
    }
    return ret;
  }

  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198 */
  void erase_edge(int a, int b) {
    if (match_l[a] == b) {
      match_l[a] = -1;
      match_r[b] = -1;
    }
    g[a].erase(find(std::begin(g[a]), std::end(g[a]), b));
    rg[b].erase(find(std::begin(rg[b]), std::end(rg[b]), a));
  }

  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334 */
  std::vector<std::pair<int, int> > lex_max_matching() {
    int matching_size = (int)max_matching().size();
    int dummy_size = (int)n - matching_size;
    BipartiteFlow aux(n, m + dummy_size);
    for (int i = 0; i < (int)n; i++) {
      for (auto& j : g[i]) aux.add_edge(i, j);
      for (int j = 0; j < dummy_size; j++) aux.add_edge(i, m + j);
    }
    auto es = aux.lex_left_perfect_matching();
    std::vector<std::pair<int, int> > ret;
    for (auto& [a, b] : es) {
      if (b < (int)m) ret.emplace_back(a, b);
    }
    return ret;
  }

  std::vector<int> min_vertex_cover() {
    auto visited = find_residual_path();
    std::vector<int> ret;
    for (int i = 0; i < (int)(n + m); i++) {
      if (visited[i] ^ (i < (int)n)) {
        ret.emplace_back(i);
      }
    }
    return ret;
  }

  /* https://atcoder.jp/contests/utpc2013/tasks/utpc2013_11 */
  std::vector<int> lex_min_vertex_cover(const std::vector<int>& ord) {
    assert(ord.size() == n + m);
    auto res = build_risidual_graph();
    std::vector<std::vector<int> > r_res(n + m + 2);
    for (int i = 0; i < (int)(n + m + 2); i++) {
      for (auto& j : res[i]) r_res[j].emplace_back(i);
    }
    std::queue<int> que;
    std::vector<int> visited(n + m + 2, -1);
    auto expand_left = [&](int t) {
      if (visited[t] != -1) return;
      que.emplace(t);
      visited[t] = 1;
      while (!que.empty()) {
        int idx = que.front();
        que.pop();
        for (auto& to : r_res[idx]) {
          if (visited[to] != -1) continue;
          visited[to] = 1;
          que.emplace(to);
        }
      }
    };
    auto expand_right = [&](int t) {
      if (visited[t] != -1) return;
      que.emplace(t);
      visited[t] = 0;
      while (!que.empty()) {
        int idx = que.front();
        que.pop();
        for (auto& to : res[idx]) {
          if (visited[to] != -1) continue;
          visited[to] = 0;
          que.emplace(to);
        }
      }
    };
    expand_right(n + m);
    expand_left(n + m + 1);
    std::vector<int> ret;
    for (auto& t : ord) {
      if (t < (int)n) {
        expand_left(t);
        if (visited[t] & 1) ret.emplace_back(t);
      } else {
        expand_right(t);
        if (~visited[t] & 1) ret.emplace_back(t);
      }
    }
    return ret;
  }

  std::vector<int> max_independent_set() {
    auto visited = find_residual_path();
    std::vector<int> ret;
    for (int i = 0; i < (int)(n + m); i++) {
      if (visited[i] ^ (i >= (int)n)) {
        ret.emplace_back(i);
      }
    }
    return ret;
  }

  std::vector<std::pair<int, int> > min_edge_cover() {
    auto es = max_matching();
    for (int i = 0; i < (int)n; i++) {
      if (match_l[i] >= 0) {
        continue;
      }
      if (g[i].empty()) {
        return {};
      }
      es.emplace_back(i, g[i][0]);
    }
    for (int i = 0; i < (int)m; i++) {
      if (match_r[i] >= 0) {
        continue;
      }
      if (rg[i].empty()) {
        return {};
      }
      es.emplace_back(rg[i][0], i);
    }
    return es;
  }

  // left: [0,n), right: [n,n+m), S: n+m, T: n+m+1
  std::vector<std::vector<int> > build_risidual_graph() {
    if (!matched) max_matching();
    const std::size_t S = n + m;
    const std::size_t T = n + m + 1;
    std::vector<std::vector<int> > ris(n + m + 2);
    for (int i = 0; i < (int)n; i++) {
      if (match_l[i] == -1)
        ris[S].emplace_back(i);
      else
        ris[i].emplace_back(S);
    }
    for (int i = 0; i < (int)m; i++) {
      if (match_r[i] == -1)
        ris[i + n].emplace_back(T);
      else
        ris[T].emplace_back(i + n);
    }
    for (int i = 0; i < (int)n; i++) {
      for (auto& j : g[i]) {
        if (match_l[i] == j)
          ris[j + n].emplace_back(i);
        else
          ris[i].emplace_back(j + n);
      }
    }
    return ris;
  }

 private:
  std::vector<std::pair<int, int> > lex_left_perfect_matching() {
    auto es = max_matching();
    assert(es.size() == n);
    for (auto& vs : g) std::sort(std::begin(vs), std::end(vs));
    es.clear();
    for (int i = 0; i < (int)n; i++) {
      match_r[match_l[i]] = -1;
      match_l[i] = -1;
      ++time_stamp;
      find_augment_path(i);
      alive[i] = 0;
      es.emplace_back(i, match_l[i]);
    }
    return es;
  }

  std::vector<int> find_residual_path() {
    auto res = build_risidual_graph();
    std::queue<int> que;
    std::vector<int> visited(n + m + 2);
    que.emplace(n + m);
    visited[n + m] = true;
    while (!que.empty()) {
      int idx = que.front();
      que.pop();
      for (auto& to : res[idx]) {
        if (visited[to]) continue;
        visited[to] = true;
        que.emplace(to);
      }
    }
    return visited;
  }

  void build_augment_path() {
    std::queue<int> que;
    dist.assign(g.size(), -1);
    for (int i = 0; i < (int)n; i++) {
      if (match_l[i] == -1) {
        que.emplace(i);
        dist[i] = 0;
      }
    }
    while (!que.empty()) {
      int a = que.front();
      que.pop();
      for (auto& b : g[a]) {
        int c = match_r[b];
        if (c >= 0 && dist[c] == -1) {
          dist[c] = dist[a] + 1;
          que.emplace(c);
        }
      }
    }
  }

  bool find_min_dist_augment_path(int a) {
    used[a] = time_stamp;
    for (auto& b : g[a]) {
      int c = match_r[b];
      if (c < 0 || (used[c] != (int)time_stamp && dist[c] == dist[a] + 1 &&
                    find_min_dist_augment_path(c))) {
        match_r[b] = a;
        match_l[a] = b;
        return true;
      }
    }
    return false;
  }

  bool find_augment_path(int a) {
    used[a] = time_stamp;
    for (auto& b : g[a]) {
      int c = match_r[b];
      if (c < 0 || (alive[c] == 1 && used[c] != (int)time_stamp &&
                    find_augment_path(c))) {
        match_r[b] = a;
        match_l[a] = b;
        return true;
      }
    }
    return false;
  }
};
