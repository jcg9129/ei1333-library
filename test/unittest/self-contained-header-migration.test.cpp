// competitive-verifier: STANDALONE

#include <cassert>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "../../graph/connected-components/bi-connected-components.hpp"
#include "../../graph/connected-components/incremental-bridge-connectivity.hpp"
#include "../../graph/connected-components/strongly-connected-components.hpp"
#include "../../graph/connected-components/three-edge-connected-components.hpp"
#include "../../graph/connected-components/two-edge-connected-components.hpp"
#include "../../graph/others/block-cut-tree.hpp"
#include "../../math/fps/bell.hpp"
#include "../../math/fps/berlekamp-massey.hpp"
#include "../../math/fps/bernoulli.hpp"
#include "../../math/fps/binomial-prefix-sum.hpp"
#include "../../math/fps/coeff-of-rational-function.hpp"
#include "../../math/fps/composition-of-formal-power-series.hpp"
#include "../../math/fps/compositional-inverse-of-formal-power-series.hpp"
#include "../../math/fps/count-subset-sum.hpp"
#include "../../math/fps/enumerate-coefficients-of-powers.hpp"
#include "../../math/fps/eulerian.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/kth-term-of-linearly-recurrent-sequence.hpp"
#include "../../math/fps/multipoint-evaluation.hpp"
#include "../../math/fps/partition.hpp"
#include "../../math/fps/polynomial-interpolation.hpp"
#include "../../math/fps/stirling-first.hpp"
#include "../../math/fps/stirling-second.hpp"
#include "../../math/fps/subproduct-tree.hpp"
#include "../../string/aho-corasick.hpp"
#include "../../string/lcp-array.hpp"
#include "../../string/longest-common-substring.hpp"
#include "../../string/palindromic-tree.hpp"
#include "../../string/rolling-hash.hpp"
#include "../../string/suffix-array.hpp"
#include "../../string/wildcard-pattern-matching.hpp"
#include "../../structure/segment-tree/dual-segment-tree.hpp"
#include "../../structure/segment-tree/lazy-segment-tree.hpp"
#include "../../structure/segment-tree/persistent-segment-tree.hpp"
#include "../../structure/segment-tree/range-linear-add-range-min-segment-tree.hpp"
#include "../../structure/segment-tree/range-tree.hpp"
#include "../../structure/segment-tree/segment-tree-beats.hpp"
#include "../../structure/trie/trie.hpp"
#include "../../graph/mst/boruvka.hpp"
#include "../../graph/mst/manhattan-mst.hpp"
#include "../../graph/others/cartesian-tree.hpp"
#include "../../graph/others/chromatic-number.hpp"
#include "../../graph/others/cycle-detection.hpp"
#include "../../graph/others/dominator-tree.hpp"
#include "../../graph/others/enumerate-cliques.hpp"
#include "../../graph/others/enumerate-triangles.hpp"
#include "../../graph/others/eulerian-trail.hpp"
#include "../../graph/others/extreme-vertex-set.hpp"
#include "../../graph/others/low-link.hpp"
#include "../../graph/others/maximum-clique.hpp"
#include "../../graph/others/maximum-independent-set.hpp"
#include "../../graph/others/minimum-steiner-tree.hpp"
#include "../../graph/others/namori-graph.hpp"
#include "../../graph/others/offline-dag-reachability.hpp"
#include "../../graph/others/topological-sort.hpp"
#include "../../graph/others/tree-decomposition-width-2.hpp"
#include "../../graph/tree/centroid.hpp"
#include "../../graph/tree/convert-rooted-tree.hpp"
#include "../../graph/tree/heavy-light-decomposition.hpp"
#include "../../graph/tree/rerooting.hpp"
#include "../../graph/tree/tree-diameter.hpp"
#include "../../math/matrix/binary-basis.hpp"
#include "../../other/connected-grid-states.hpp"
#include "../../other/dynamic-point-add-rectangle-sum.hpp"
#include "../../other/dynamic-rectangle-add-point-get.hpp"
#include "../../other/mo-rollback.hpp"
#include "../../other/mo.hpp"
#include "../../other/offline-dynamic-connectivity.hpp"
#include "../../other/poyopoyo-pudding.hpp"
#include "../../other/scanner.hpp"
#include "../../other/static-point-add-rectangle-sum.hpp"
#include "../../other/static-range-count-distinct.hpp"
#include "../../other/static-rectangle-add-point-get.hpp"
#include "../../other/static-rectangle-add-rectangle-sum.hpp"
#include "../../other/timer.hpp"
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
#include "../../geometry/angle.hpp"
#include "../../geometry/area.hpp"
#include "../../geometry/base.hpp"
#include "../../geometry/ccw.hpp"
#include "../../geometry/circle.hpp"
#include "../../geometry/common_area_cp.hpp"
#include "../../geometry/contains.hpp"
#include "../../geometry/convex-layers.hpp"
#include "../../geometry/convex_hull.hpp"
#include "../../geometry/convex_polygon_contains.hpp"
#include "../../geometry/convex_polygon_cut.hpp"
#include "../../geometry/convex_polygon_diameter.hpp"
#include "../../geometry/cross_point_cc.hpp"
#include "../../geometry/cross_point_cl.hpp"
#include "../../geometry/cross_point_cs.hpp"
#include "../../geometry/cross_point_ll.hpp"
#include "../../geometry/distance_ll.hpp"
#include "../../geometry/distance_lp.hpp"
#include "../../geometry/distance_pp.hpp"
#include "../../geometry/distance_sp.hpp"
#include "../../geometry/distance_ss.hpp"
#include "../../geometry/integer/point.hpp"
#include "../../geometry/is_convex_polygon.hpp"
#include "../../geometry/is_intersect_cl.hpp"
#include "../../geometry/is_intersect_cp.hpp"
#include "../../geometry/is_intersect_cs.hpp"
#include "../../geometry/is_intersect_ll.hpp"
#include "../../geometry/is_intersect_lp.hpp"
#include "../../geometry/is_intersect_ls.hpp"
#include "../../geometry/is_intersect_sp.hpp"
#include "../../geometry/is_intersect_ss.hpp"
#include "../../geometry/is_orthogonal.hpp"
#include "../../geometry/is_parallel.hpp"
#include "../../geometry/line.hpp"
#include "../../geometry/point.hpp"
#include "../../geometry/polygon.hpp"
#include "../../geometry/projection.hpp"
#include "../../geometry/reflection.hpp"
#include "../../geometry/segment.hpp"
#include "../../graph/graph-template.hpp"
#include "../../graph/shortest-path/bellman-ford.hpp"
#include "../../graph/shortest-path/bfs.hpp"
#include "../../graph/shortest-path/dijkstra.hpp"
#include "../../graph/shortest-path/grid-bfs.hpp"
#include "../../graph/shortest-path/warshall-floyd.hpp"
#include "../../math/combinatorics/binomial-table.hpp"
#include "../../math/combinatorics/arbitrary-mod-int.hpp"
#include "../../math/combinatorics/bell-number.hpp"
#include "../../math/combinatorics/binomial-prefix-sum-query.hpp"
#include "../../math/combinatorics/binomial.hpp"
#include "../../math/combinatorics/count-bounded-increasing-sequences.hpp"
#include "../../math/combinatorics/enumeration.hpp"
#include "../../math/combinatorics/factorial.hpp"
#include "../../math/combinatorics/lagrange-polynomial-2.hpp"
#include "../../math/combinatorics/lagrange-polynomial-3.hpp"
#include "../../math/combinatorics/lagrange-polynomial.hpp"
#include "../../math/combinatorics/mod-log.hpp"
#include "../../math/combinatorics/mod-pow.hpp"
#include "../../math/combinatorics/mod-sqrt.hpp"
#include "../../math/combinatorics/mod-tetration.hpp"
#include "../../math/combinatorics/modint-2-61m1.hpp"
#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/combinatorics/montmort.hpp"
#include "../../math/combinatorics/partition-table.hpp"
#include "../../math/combinatorics/sample-point-shift.hpp"
#include "../../math/combinatorics/sum-of-arithmetic-sequence.hpp"
#include "../../math/combinatorics/sum-of-geometric-sequence.hpp"
#include "../../math/combinatorics/stirling-number-second.hpp"
#include "../../math/combinatorics/vectorize-mod-int.hpp"
#include "../../math/fft/arbitrary-mod-convolution-long.hpp"
#include "../../math/fft/arbitrary-mod-convolution.hpp"
#include "../../math/fft/bitwise-and-convolution.hpp"
#include "../../math/fft/bitwise-or-convolution.hpp"
#include "../../math/fft/bitwise-xor-convolution.hpp"
#include "../../math/fft/fast-fourier-transform.hpp"
#include "../../math/fft/fast-walsh-hadamard-transform.hpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.hpp"
#include "../../math/fft/number-theoretic-transform.hpp"
#include "../../math/fft/subset-convolution.hpp"
#include "../../math/fft/subset-zeta-moebius-transform.hpp"
#include "../../math/fft/superset-zeta-moebius-transform-simd.hpp"
#include "../../math/fft/superset-zeta-moebius-transform.hpp"
#include "../../math/matrix/matrix.hpp"
#include "../../math/matrix/square-matrix.hpp"
#include "../../math/number-theory/convert-base.hpp"
#include "../../math/number-theory/divisor.hpp"
#include "../../math/number-theory/enumerate-quotients.hpp"
#include "../../math/number-theory/euler-phi-table.hpp"
#include "../../math/number-theory/euler-phi.hpp"
#include "../../math/number-theory/enumerate-primes.hpp"
#include "../../math/number-theory/extgcd.hpp"
#include "../../math/number-theory/fast-prime-factorization.hpp"
#include "../../math/number-theory/is-prime.hpp"
#include "../../math/number-theory/kth-root-integer.hpp"
#include "../../math/number-theory/moebius-mu-table.hpp"
#include "../../math/number-theory/prime-factor.hpp"
#include "../../math/number-theory/prime-count.hpp"
#include "../../math/number-theory/prime-table.hpp"
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
#include "../../other/offline-rmq.hpp"
#include "../../other/static-range-frequency.hpp"
#include "../../string/manacher.hpp"
#include "../../string/z-algorithm.hpp"
#include "../../structure/class/act.hpp"
#include "../../structure/class/acted-monoid.hpp"
#include "../../structure/class/affine.hpp"
#include "../../structure/class/beats-monoid.hpp"
#include "../../structure/class/monoid.hpp"
#include "../../structure/class/point-add-rectangle-sum.hpp"
#include "../../structure/class/point-set-range-composite.hpp"
#include "../../structure/class/range-add-range-min.hpp"
#include "../../structure/class/range-chmin-chmax-add-range-sum.hpp"
#include "../../structure/class/range-affine-range-sum.hpp"
#include "../../structure/others/decremental-upper-hull.hpp"
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
  assert(binomial<double>(5, 2) == 10);
  assert(mod_pow(2, 10, 1000) == 24);
  assert(mod_sqrt(4, 7) == 2 || mod_sqrt(4, 7) == 5);
  assert(mod_log(2, 8, 13) == 3);
  assert(mod_tetration(2, 3, 1000) == 16);
  assert(prime_table(10)[7] && !prime_table(10)[9]);
  assert(enumerate_primes(10) == std::vector<int>({2, 3, 5, 7}));
  assert(FastPrimeFactorization::prime_factor(84) ==
         std::vector<std::uint64_t>({2, 2, 3, 7}));
  StaticRangeFrequency<int> frequency({1, 2, 1, 3, 1});
  assert(frequency.query(1, 5, 1) == 2);

  std::vector<double> hadamard{1, 2, 3, 4};
  fast_walsh_hadamard_transform(hadamard);
  fast_walsh_hadamard_transform(hadamard, true);
  assert(hadamard == std::vector<double>({1, 2, 3, 4}));
  assert(bitwise_and_convolution(std::vector<int>{1, 0, 0, 0},
                                 std::vector<int>{1, 1, 1, 1})
             .size() == 4);

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
  std::vector<std::vector<int>> distances{{0, 1}, {1, 0}};
  warshall_floyd(distances, 100);
  assert(distances[0][1] == 1);
  std::vector<std::string> grid{"S.", ".#"};
  assert(grid_bfs(grid, 'S')[0][1] == 1);
  Graph<int> dag(3);
  dag.add_directed_edge(0, 1);
  dag.add_directed_edge(1, 2);
  assert(topological_sort(dag).size() == 3);

  BinaryBasis<int> binary_basis;
  assert(binary_basis.add(1) && binary_basis.add(2));
  assert(binary_basis.check(3) && binary_basis.size() == 2);
  assert(cartesian_tree(std::vector<int>{3, 1, 2})[0] == 1);
  StaticRangeCountDistinct<int> distinct({1, 2, 1, 3});
  distinct.add_query(0, 4);
  assert(distinct.calclate_queries()[0] == 3);
  PoyoPoyoPudding pudding;
  assert(pudding.addLayer(50, 50) && pudding.eatTop());

  using geometry::Circle;
  using geometry::Line;
  using geometry::Point;
  using geometry::Polygon;
  using geometry::Segment;
  Point a(0, 0), b(3, 4);
  assert(geometry::distance(a, b) == 5);
  assert(geometry::equals(geometry::cross(a, b), 0));
  Line line(a, b);
  Segment segment(Point(0, 4), Point(3, 0));
  assert(geometry::is_intersect_ls(line, segment));
  assert(geometry::is_orthogonal(Line(Point(0, 0), Point(1, 0)),
                                 Line(Point(0, 0), Point(0, 1))));
  Circle circle(Point(0, 0), 1);
  assert(geometry::is_intersect_cp(circle, Point(1, 0)));
  Polygon polygon{Point(0, 0), Point(2, 0), Point(0, 2)};
  assert(geometry::area(polygon) == 2);
  assert(geometry::contains(polygon, Point(1, 1)) == geometry::ON);
  std::vector<Point> hull = geometry::convex_hull(polygon);
  assert(hull.size() == 3);
  DecrementalUpperHull<int, long long> upper_hull(
      std::vector<std::pair<int, int>>{{0, 0}, {1, 1}, {2, 0}});
  assert(upper_hull.size() == 3);
  assert((convex_layers<int, long long>({{0, 0}, {1, 0}, {0, 1}}) ==
          std::vector<int>({1, 1, 1})));
}
