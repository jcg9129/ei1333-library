// competitive-verifier: STANDALONE

#include <cassert>
#include <functional>
#include <string>
#include <vector>

#include "../../dp/cumulative-sum-2d.hpp"
#include "../../dp/cumulative-sum.hpp"
#include "../../dp/edit-distance.hpp"
#include "../../dp/knapsack-01-2.hpp"
#include "../../dp/knapsack-01.hpp"
#include "../../dp/knapsack-limitations.hpp"
#include "../../dp/knapsack.hpp"
#include "../../dp/largest-rectangle.hpp"
#include "../../dp/longest-increasing-subsequence.hpp"
#include "../../dp/monotone-minima.hpp"
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
}
