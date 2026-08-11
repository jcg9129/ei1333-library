// competitive-verifier: STANDALONE

#include "../../graph/connected-components/strongly-connected-components.hpp"

#include <cassert>
#include <random>
#include <vector>

int main() {
  {
    StronglyConnectedComponents<> graph(8);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(2, 0);
    graph.add_directed_edge(2, 3);
    graph.add_directed_edge(3, 4);
    graph.add_directed_edge(4, 3);
    graph.add_directed_edge(4, 5);
    graph.add_directed_edge(6, 7);
    graph.build();

    assert(graph[0] == graph[1] && graph[1] == graph[2]);
    assert(graph[3] == graph[4]);
    assert(graph[2] != graph[3]);
    assert(graph[3] != graph[5]);
    assert(graph[6] != graph[7]);
    assert(graph[2] < graph[3] && graph[3] < graph[5]);
    assert(graph[6] < graph[7]);

    graph.add_directed_edge(5, 0);
    graph.build();
    for (int v = 1; v <= 5; v++) assert(graph[v] == graph[0]);
    int grouped_vertices = 0;
    for (const auto& component : graph.group) {
      grouped_vertices += static_cast<int>(component.size());
    }
    assert(grouped_vertices == 8);
  }

  std::mt19937 rng(123456789);
  for (int n = 1; n <= 30; n++) {
    for (int iteration = 0; iteration < 30; iteration++) {
      StronglyConnectedComponents<> graph(n);
      std::vector<std::vector<bool>> reachable(n, std::vector<bool>(n, false));
      for (int v = 0; v < n; v++) reachable[v][v] = true;
      for (int from = 0; from < n; from++) {
        for (int to = 0; to < n; to++) {
          if (rng() % 5 == 0) {
            graph.add_directed_edge(from, to);
            reachable[from][to] = true;
          }
        }
      }
      for (int k = 0; k < n; k++) {
        for (int from = 0; from < n; from++) {
          for (int to = 0; to < n; to++) {
            reachable[from][to] =
                reachable[from][to] || (reachable[from][k] && reachable[k][to]);
          }
        }
      }

      graph.build();
      for (int from = 0; from < n; from++) {
        for (int to = 0; to < n; to++) {
          bool same_component = reachable[from][to] && reachable[to][from];
          assert((graph[from] == graph[to]) == same_component);
          if (reachable[from][to] && graph[from] != graph[to]) {
            assert(graph[from] < graph[to]);
          }
        }
      }
    }
  }

  {
    constexpr int kVertices = 300000;
    StronglyConnectedComponents<> graph(kVertices);
    for (int v = 1; v < kVertices; v++) {
      graph.add_directed_edge(v - 1, v);
    }
    graph.build();
    assert(graph.group.size() == kVertices);
    assert(graph[0] == 0);
    assert(graph[kVertices - 1] == kVertices - 1);
  }
}
