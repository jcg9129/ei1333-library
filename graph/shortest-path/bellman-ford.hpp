#pragma once

#include <algorithm>
#include <limits>
#include <vector>

#include "../graph-template.hpp"

template <typename T>
std::vector<T> bellman_ford(const Edges<T>& edges, int n, int s) {
  const auto INF = std::numeric_limits<T>::max();
  const auto M_INF = std::numeric_limits<T>::min();
  std::vector<T> dist(n, INF);
  dist[s] = 0;
  for (int i = 0; i < n - 1; i++) {
    for (auto& e : edges) {
      if (dist[e.from] == INF) continue;
      dist[e.to] = std::min(dist[e.to], dist[e.from] + e.cost);
    }
  }
  std::vector<bool> negative(n);
  for (int i = 0; i < n; i++) {
    for (auto& e : edges) {
      if (dist[e.from] == INF) continue;
      if (dist[e.from] + e.cost < dist[e.to]) {
        dist[e.to] = dist[e.from] + e.cost;
        negative[e.to] = true;
      }
      if (negative[e.from]) {
        negative[e.to] = true;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (negative[i]) dist[i] = M_INF;
  }
  return dist;
}
