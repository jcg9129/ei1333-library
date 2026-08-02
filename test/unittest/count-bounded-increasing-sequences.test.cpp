// competitive-verifier: STANDALONE

// clang-format off
#include "../../template/template.hpp"
// clang-format on

#include "../../math/combinatorics/count-bounded-increasing-sequences.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

using mint = modint998244353;

mint naive(const vector<int> &lower_bounds, const vector<int> &upper_bounds) {
  if (upper_bounds.empty()) return 1;
  vector<mint> dp(*max_element(upper_bounds.begin(), upper_bounds.end()) + 1);
  for (int value = lower_bounds[0]; value <= upper_bounds[0]; value++) {
    dp[value] = 1;
  }
  for (int i = 1; i < (int)upper_bounds.size(); i++) {
    mint sum = 0;
    vector<mint> next(dp.size());
    for (int value = 0; value <= upper_bounds[i]; value++) {
      sum += dp[value];
      if (value >= lower_bounds[i]) next[value] = sum;
    }
    dp = move(next);
  }
  mint answer = 0;
  for (int value = 0; value <= upper_bounds.back(); value++) {
    answer += dp[value];
  }
  return answer;
}

void check(const vector<int> &lower_bounds, const vector<int> &upper_bounds) {
  auto got =
      count_bounded_increasing_sequences<FormalPowerSeriesFriendlyNTT, mint>(
          lower_bounds, upper_bounds);
  auto expected = naive(lower_bounds, upper_bounds);
  if (got != expected) {
    cerr << "lower:";
    for (auto x : lower_bounds) cerr << ' ' << x;
    cerr << "\nupper:";
    for (auto x : upper_bounds) cerr << ' ' << x;
    cerr << "\ngot: " << got << ", expected: " << expected << '\n';
    assert(false);
  }
}

int main() {
  check({}, {});
  check({0}, {0});
  check({0}, {10});
  check({0, 0, 0, 0}, {0, 0, 0, 0});
  check({0, 0, 0, 0, 0}, {0, 2, 2, 3, 5});
  check({0, 0, 0, 0, 0, 0}, {1, 1, 3, 3, 3, 8});
  check({0, 0, 0, 0, 0}, {5, 4, 7, 6, 8});
  check({3}, {10});
  check({0, 1, 1, 3, 3}, {0, 2, 2, 3, 5});
  check({2, 0, 4, 1, 3}, {5, 4, 7, 6, 8});
  check({0, 5}, {3, 4});
  check({4, 4, 4}, {6, 6, 8});
  check({0, 1, 2, 3, 4, 5}, {20, 21, 22, 23, 24, 25});

  mt19937_64 rng(123456789);
  for (int n = 1; n <= 30; n++) {
    for (int rep = 0; rep < 100; rep++) {
      vector<int> upper_bounds(n);
      for (int i = 0; i < n; i++) upper_bounds[i] = rng() % 50;
      sort(upper_bounds.begin(), upper_bounds.end());
      check(vector<int>(n), upper_bounds);

      vector<int> lower_bounds(n);
      for (int i = 0; i < n; i++) {
        lower_bounds[i] = rng() % 50;
        upper_bounds[i] = rng() % 50;
      }
      check(lower_bounds, upper_bounds);

      for (int i = 0; i < n; i++) lower_bounds[i] = rng() % 30;
      sort(lower_bounds.begin(), lower_bounds.end());
      for (int i = 0; i < n; i++) {
        upper_bounds[i] = lower_bounds[i] + rng() % 30;
        if (i > 0) upper_bounds[i] = max(upper_bounds[i], upper_bounds[i - 1]);
      }
      check(lower_bounds, upper_bounds);
    }
  }
}
