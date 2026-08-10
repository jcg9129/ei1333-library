#pragma once

#include <cstddef>
#include <vector>

#include "../connected-components/strongly-connected-components.hpp"

/**
 * @brief Two Satisfiability(2-SAT)
 *
 */
struct TwoSatisfiability : StronglyConnectedComponents<bool> {
 public:
  using StronglyConnectedComponents<bool>::g;
  using StronglyConnectedComponents<bool>::comp;
  using StronglyConnectedComponents<bool>::add_edge;
  std::size_t sz;

  explicit TwoSatisfiability(std::size_t v)
      : StronglyConnectedComponents<bool>(v + v), sz(v) {}

  void add_if(int u, int v) {
    // u -> v <=> !v -> !u
    add_directed_edge(u, v);
    add_directed_edge(rev(v), rev(u));
  }

  void add_or(int u, int v) {
    // u or v <=> !u -> v
    add_if(rev(u), v);
  }

  void add_nand(int u, int v) {
    // u nand v <=> u -> !v
    add_if(u, rev(v));
  }

  void set_true(int u) {
    // u <=> !u -> u
    add_directed_edge(rev(u), u);
  }

  void set_false(int u) {
    // !u <=> u -> !u
    add_directed_edge(u, rev(u));
  }

  inline int rev(int x) {
    if (x >= (int)sz) return x - sz;
    return x + sz;
  }

  std::vector<int> solve() {
    StronglyConnectedComponents<bool>::build();
    std::vector<int> ret(sz);
    for (std::size_t i = 0; i < sz; i++) {
      if (comp[i] == comp[rev(i)]) return {};
      ret[i] = comp[i] > comp[rev(i)];
    }
    return ret;
  }
};
