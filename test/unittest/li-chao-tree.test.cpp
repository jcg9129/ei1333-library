// competitive-verifier: STANDALONE

#include "../../template/template.hpp"

#include "../../structure/convex-hull-trick/li-chao-tree.hpp"

namespace {

using int64 = long long;

constexpr int64 INF = 4'000'000'000'000'000'000LL;

void check(const vector<int64>& coordinates,
           const vector<pair<int64, int64>>& lines) {
  LiChaoTree<int64> tree(coordinates, INF);
  for (auto [a, b] : lines) tree.update(a, b);

  vector<int64> xs = coordinates;
  sort(begin(xs), end(xs));
  xs.erase(unique(begin(xs), end(xs)), end(xs));
  for (int i = 0; i < (int)xs.size(); i++) {
    int64 expected = INF;
    for (auto [a, b] : lines) expected = min(expected, a * xs[i] + b);
    assert(tree.query(i) == expected);
  }
}

}  // namespace

int main() {
  check({5, -3, 5, 1, -3}, {{2, 4}, {-1, 7}, {0, -2}});
  check({42, 42, 42}, {});
  check({42, 42, 42}, {{-3, 100}, {2, -100}});
  check({numeric_limits<int64>::max(), -1, 0}, {{0, 5}, {0, -3}});

  mt19937_64 rng(123456789);
  for (int rep = 0; rep < 500; rep++) {
    int n = 1 + rng() % 30;
    vector<int64> coordinates(n);
    for (auto& x : coordinates) x = (int64)(rng() % 21) - 10;
    shuffle(begin(coordinates), end(coordinates), rng);

    int m = rng() % 30;
    vector<pair<int64, int64>> lines(m);
    for (auto& [a, b] : lines) {
      a = (int64)(rng() % 21) - 10;
      b = (int64)(rng() % 101) - 50;
    }
    check(coordinates, lines);
  }
}
