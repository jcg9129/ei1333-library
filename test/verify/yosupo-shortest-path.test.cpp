// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shortest_path
// clang-format on

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../graph/graph-template.hpp"
#include "../../graph/shortest-path/dijkstra.hpp"

using namespace std;

int main() {
  int N, M, S, T;
  cin >> N >> M >> S >> T;
  Graph<long long> g(N);
  g.read(M, 0, true, true);
  auto ret = dijkstra(g, S);
  if (ret.from[T] == -1) {
    cout << -1 << "\n";
  } else {
    cout << ret.dist[T] << " ";
    vector<pair<int, int>> es;
    while (S != T) {
      es.emplace_back(ret.from[T], T);
      T = ret.from[T];
    }
    reverse(begin(es), end(es));
    cout << es.size() << "\n";
    for (auto& p : es) cout << p.first << " " << p.second << "\n";
  }
}
