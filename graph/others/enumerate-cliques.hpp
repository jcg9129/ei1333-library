#pragma once

#include <cmath>
#include <queue>
#include <vector>

/**
 * @brief Enumerate Cliques(クリーク全列挙)
 * @see https://www.slideshare.net/wata_orz/ss-12131479
 *
 */
template <typename Matrix>
std::vector<std::vector<int> > enumerate_cliques(Matrix& g) {
  int N = (int)g.size(), M = 0;
  std::vector<int> deg(N);
  std::vector<std::vector<int> > edge(N, std::vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (auto p : g[i]) deg[i] += p;
    M += deg[i];
  }
  int lim = (int)std::sqrt(M);

  std::vector<std::vector<int> > cliques;

  auto add_clique = [&](const std::vector<int>& rem, bool last) {
    std::vector<int> neighbor((int)rem.size() - last);
    for (int i = 0; i < (int)neighbor.size(); i++) {
      for (int j = 0; j < (int)neighbor.size(); j++) {
        if (i != j && !g[rem[i]][rem[j]]) neighbor[i] |= 1 << j;
      }
    }
    for (int i = 1 - last; i < (1 << neighbor.size()); i++) {
      bool ok = true;
      for (int j = 0; j < (int)neighbor.size(); j++) {
        if ((i >> j) & 1) {
          if (i & neighbor[j]) {
            ok = false;
            break;
          }
        }
      }
      if (ok) {
        std::vector<int> clique;
        if (last) clique.emplace_back(rem.back());
        for (int j = 0; j < (int)neighbor.size(); j++) {
          if ((i >> j) & 1) clique.emplace_back(rem[j]);
        }
        cliques.emplace_back(clique);
      }
    }
  };

  std::vector<int> used(N);
  std::queue<int> que;
  for (int i = 0; i < N; i++) {
    if (deg[i] < lim) {
      used[i] = true;
      que.emplace(i);
    }
  }
  while (!que.empty()) {
    int idx = que.front();
    que.pop();
    std::vector<int> rem;
    for (int k = 0; k < N; k++) {
      if (g[idx][k]) rem.emplace_back(k);
    }
    rem.emplace_back(idx);
    add_clique(rem, true);
    used[idx] = true;
    for (int k = 0; k < N; k++) {
      if (g[idx][k]) {
        g[idx][k] = false;
        g[k][idx] = false;
        --deg[k];
        if (!used[k] && deg[k] < lim) {
          used[k] = true;
          que.emplace(k);
        }
      }
    }
  }
  std::vector<int> rem;
  for (int i = 0; i < N; i++) {
    if (!used[i]) rem.emplace_back(i);
  }
  add_clique(rem, false);
  return cliques;
}
#pragma once
