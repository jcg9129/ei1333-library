// competitive-verifier: STANDALONE

#include <cassert>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "../../dp/cumulative-sum-2d.hpp"
#include "../../dp/cumulative-sum.hpp"
#include "../../dp/divide-and-conquer-optimization.hpp"
#include "../../dp/edit-distance.hpp"
#include "../../dp/knapsack-01-2.hpp"
#include "../../dp/knapsack-01.hpp"
#include "../../dp/knapsack-limitations-2.hpp"
#include "../../dp/knapsack-limitations.hpp"
#include "../../dp/knapsack.hpp"
#include "../../dp/largest-rectangle.hpp"
#include "../../dp/longest-increasing-subsequence.hpp"
#include "../../dp/monotone-minima.hpp"
#include "../../dp/online-offline-dp.hpp"
#include "../../graph/graph-template.hpp"
#include "../../graph/shortest-path/bellman-ford.hpp"
#include "../../graph/shortest-path/bfs.hpp"
#include "../../graph/shortest-path/dijkstra.hpp"
#include "../../graph/shortest-path/grid-bfs.hpp"
#include "../../graph/shortest-path/warshall-floyd.hpp"
#include "../../math/combinatorics/binomial-table.hpp"
#include "../../math/combinatorics/enumeration.hpp"
#include "../../math/combinatorics/montmort.hpp"
#include "../../math/combinatorics/partition-table.hpp"
#include "../../math/combinatorics/sum-of-arithmetic-sequence.hpp"
#include "../../math/combinatorics/sum-of-geometric-sequence.hpp"
#include "../../math/matrix/matrix.hpp"
#include "../../math/matrix/square-matrix.hpp"
#include "../../math/number-theory/convert-base.hpp"
#include "../../math/number-theory/divisor.hpp"
#include "../../math/number-theory/enumerate-quotients.hpp"
#include "../../math/number-theory/euler-phi-table.hpp"
#include "../../math/number-theory/euler-phi.hpp"
#include "../../math/number-theory/extgcd.hpp"
#include "../../math/number-theory/is-prime.hpp"
#include "../../math/number-theory/kth-root-integer.hpp"
#include "../../math/number-theory/moebius-mu-table.hpp"
#include "../../math/number-theory/prime-factor.hpp"
#include "../../math/number-theory/sum-of-floor-of-linear.hpp"
#include "../../math/rational/rational.hpp"
#include "../../other/ceil-div.hpp"
#include "../../other/chrono-timer.hpp"
#include "../../other/compress.hpp"
#include "../../other/dice.hpp"
#include "../../other/floor-div.hpp"
#include "../../other/printer.hpp"
#include "../../other/random-number-generator.hpp"
#include "../../other/vector-pool.hpp"
#include "../../other/xor-shift.hpp"
#include "../../string/manacher.hpp"
#include "../../string/z-algorithm.hpp"
#include "../../structure/class/act.hpp"
#include "../../structure/class/acted-monoid.hpp"
#include "../../structure/class/affine.hpp"
#include "../../structure/class/beats-monoid.hpp"
#include "../../structure/class/monoid.hpp"
#include "../../structure/class/range-add-range-min.hpp"
#include "../../structure/class/range-chmin-chmax-add-range-sum.hpp"
#include "../../structure/others/slope-trick.hpp"
#include "../../structure/others/sqrt-decomposition.hpp"
#include "../../structure/others/union-rectangle.hpp"

int main() {
  CumulativeSum<int> sum(3);
  sum.add(0, 2), sum.add(2, 5), sum.build();
  assert(sum.fold(0, 3) == 7);

  CumulativeSum2D<int> sum_2d(2, 2);
  sum_2d.add(0, 1, 3), sum_2d.add(1, 0, 4), sum_2d.build();
  assert(sum_2d.query(0, 0, 2, 2) == 7);
  assert(edit_distance("kitten", "sitting") == 3);
  assert(knapsack_01(std::vector<int>{2}, std::vector<int>{5}, 2, -1)[2] == 5);
  assert(knapsack_01_2(std::vector<int>{2}, std::vector<int>{5}, 2) == 5);
  assert(knapsack(std::vector<int>{2}, std::vector<int>{5}, 2, -1)[2] == 5);
  assert(knapsack_limitations(std::vector<int>{2}, std::vector<int>{2},
                              std::vector<int>{5}, 4, -1)[4] == 10);
  assert(largest_rectangle(std::vector<int>{2, 1, 2}) == 3);
  assert(longest_increasing_subsequence(std::vector<int>{3, 1, 2}, true) == 2);
  auto minima = monotone_minima<int>(
      2, 2, [](int i, int j) { return (i - j) * (i - j); });
  assert(minima[0].first == 0 && minima[1].first == 1);

  Affine<int> f(2, 3), g(4, 5);
  assert(Affine<int>::op(f, g).eval(1) == 25);
  assert(RangeAddRangeMin<int>::op(3, 1) == 1);
  assert(RangeChminChmaxAddRangeSum<int>::set(4).sum == 4);

  auto monoid =
      LambdaMonoid([](int a, int b) { return a + b; }, [] { return 0; });
  assert(monoid.op(2, 3) == 5 && monoid.e() == 0);
  auto act = LambdaAct([](int a, int b) { return a + b; }, [] { return 0; });
  assert(act.composition(2, 3) == 5 && act.id() == 0);
  auto acted_monoid =
      LambdaActedMonoid([](int a, int b) { return a + b; }, [] { return 0; },
                        [](int x, int f) { return x + f; },
                        [](int f, int g) { return f + g; }, [] { return 0; });
  assert(acted_monoid.mapping(2, 3) == 5);
  auto beats = LambdaBeatsMonoid(
      [](int a, int b) { return a + b; }, [](int) { return false; },
      [] { return 0; }, [](int x, int f) { return x + f; },
      [](int f, int g) { return f + g; }, [] { return 0; });
  assert(beats.mapping(2, 3) == 5 && !beats.fail(0));

  SlopeTrick<int> slope;
  slope.add_abs(3);
  assert(slope.get(3) == 0);
  UnionRectangle<int> rectangle;
  rectangle.add_point(2, 3);
  assert(rectangle.get() == 6);
  SqrtDecomposition<int> decomposition(2);
  decomposition.build({0, 1}, {4, 5});
  assert(decomposition.query(0, 2, 1) == 5);

  assert(ceil_div(-5, 2) == -2 && floor_div(-5, 2) == -3);
  Compress<int> compress({3, 1, 3});
  compress.build();
  assert(compress.get(3) == 1 && compress[0] == 1);
  assert(divisor(12) == std::vector<std::int64_t>({1, 2, 3, 4, 6, 12}));
  assert(prime_factor(12)[2] == 2 && euler_phi(12) == 4);
  assert(euler_phi_table(4) == std::vector<int>({0, 1, 1, 2, 2}));
  assert(moebius_table(4) == std::vector<int>({1, 1, -1, -1, 0}));
  assert(is_prime(97) && !is_prime(91));
  assert(kth_root_integer(1000, 3) == 10);
  assert(convert_base(5, 2) == std::vector<int>({1, 0, 1}));
  assert(sum_of_floor_of_linear(4, 3, 1, 0) == 1);
  assert(binomial_table<int>(3)[3][1] == 3);
  assert(montmort<int>(4)[4] == 9);
  assert(partition_table<int>(4, 4)[4][4] == 5);
  assert(sum_of_arithmetic_sequence(1, 2, 3) == 9);
  assert(Enumeration<int>::C(0, 0) == 1);

  Matrix<double> matrix{{{1, 2}, {3, 4}}};
  assert(matrix.determinant() == -2);
  Rational<int> rational(2, 4);
  assert(rational.numerator() == 1 && rational.denominator() == 2);
  assert(manacher(std::string("aba"), false)[1] == 3);
  ZAlgorithm<char> z("ababa");
  assert(z.get()[2] == 3);

  Graph<int> graph(3);
  graph.add_edge(0, 1, 1);
  graph.add_edge(1, 2, 2);
  assert(bfs(graph, 0)[2] == 3);
  assert(dijkstra(graph, 0).dist[2] == 3);
  assert(bellman_ford(Edges<int>{{0, 1, 1}, {1, 2, 2}}, 3, 0)[2] == 3);
  std::vector<std::vector<int> > distances{{0, 1}, {1, 0}};
  warshall_floyd(distances, 100);
  assert(distances[0][1] == 1);
  std::vector<std::string> grid{"S.", ".#"};
  assert(grid_bfs(grid, 'S')[0][1] == 1);
}
