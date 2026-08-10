#pragma once

#include <algorithm>
#include <cstddef>

/**
 * @brief Warshall Floyd(全点対間最短路)
 */
template <typename Matrix, typename T>
void warshall_floyd(Matrix& g, T INF) {
  for (std::size_t k = 0; k < g.size(); k++) {
    for (std::size_t i = 0; i < g.size(); i++) {
      for (std::size_t j = 0; j < g.size(); j++) {
        if (g[i][k] == INF || g[k][j] == INF) continue;
        g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}
