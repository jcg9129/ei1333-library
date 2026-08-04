// competitive-verifier: STANDALONE

#include <algorithm>
#include <cassert>
#include <vector>

#include "../../structure/union-find/bipartite-graph.hpp"
#include "../../structure/union-find/partially-persistent-union-find.hpp"
#include "../../structure/union-find/persistent-union-find.hpp"
#include "../../structure/union-find/union-find-undo.hpp"
#include "../../structure/union-find/union-find.hpp"
#include "../../structure/union-find/weighted-union-find.hpp"

int main() {
  {
    UnionFind uf(6);
    assert(uf.unite(0, 1));
    assert(uf.unite(1, 2));
    assert(!uf.unite(0, 2));
    assert(uf.same(0, 2));
    assert(!uf.same(0, 3));
    assert(uf.size(1) == 3);
    uf.unite(3, 4);
    auto groups = uf.groups();
    for (auto& group : groups) std::sort(group.begin(), group.end());
    std::sort(groups.begin(), groups.end());
    assert((groups == std::vector<std::vector<int>>{{0, 1, 2}, {3, 4}, {5}}));
  }

  {
    WeightedUnionFind<long long> uf(4);
    assert(uf.unite(0, 1, 3));
    assert(uf.unite(1, 2, -5));
    assert(uf.diff(0, 2) == -2);
    assert(uf.diff(2, 0) == 2);
    assert(!uf.unite(0, 2, -2));
  }

  {
    UnionFindUndo uf(4);
    uf.unite(0, 1);
    uf.snapshot();
    uf.unite(1, 2);
    assert(uf.size(0) == 3);
    uf.rollback();
    assert(uf.size(0) == 2);
    assert(uf.size(2) == 1);
    uf.unite(2, 3);
    uf.undo();
    assert(uf.size(2) == 1);
  }

  {
    PartiallyPersistentUnionFind uf(5);
    uf.unite(1, 0, 1);
    uf.unite(3, 1, 2);
    uf.unite(5, 3, 4);
    assert(uf.size(0, 0) == 1);
    assert(uf.size(1, 0) == 2);
    assert(uf.size(2, 2) == 1);
    assert(uf.size(3, 0) == 3);
    assert(uf.find(4, 0) == uf.find(4, 2));
    assert(uf.find(4, 0) != uf.find(4, 3));
  }

  {
    PersistentUnionFind original(5);
    auto first = original;
    first.unite(0, 1);
    auto second = first;
    second.unite(1, 2);
    assert(original.size(0) == 1);
    assert(first.size(0) == 2);
    assert(first.size(2) == 1);
    assert(second.size(0) == 3);
  }

  {
    auto add_edge = [](BipartiteGraph& graph, int n, int u, int v) {
      graph.unite(u, v + n);
      graph.unite(u + n, v);
    };

    BipartiteGraph path(3);
    add_edge(path, 3, 0, 1);
    add_edge(path, 3, 1, 2);
    assert(path.bipartite_graph_coloring());
    assert(path[0] != path[1]);
    assert(path[1] != path[2]);

    BipartiteGraph triangle(3);
    add_edge(triangle, 3, 0, 1);
    add_edge(triangle, 3, 1, 2);
    add_edge(triangle, 3, 2, 0);
    assert(!triangle.bipartite_graph_coloring());
  }
}
