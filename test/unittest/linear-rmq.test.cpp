// competitive-verifier: STANDALONE

#include "../../structure/others/linear-rmq.hpp"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

void check(const std::vector<int>& values) {
  const auto rmq = get_linear_rmq(
      values.size(), [&](int a, int b) { return values[a] < values[b]; });
  for (int left = 0; left < (int)values.size(); left++) {
    int expected = values[left];
    for (int right = left + 1; right <= (int)values.size(); right++) {
      expected = std::min(expected, values[right - 1]);
      int position = rmq.fold(left, right);
      assert(left <= position && position < right);
      assert(values[position] == expected);
    }
  }
}

int main() {
  check({42});
  check({5, 2, 7, 1, 1, 6});

  std::mt19937 rng(123456789);
  for (int n = 1; n <= 100; n++) {
    std::vector<int> values(n);
    for (int& value : values) value = (int)(rng() % 201) - 100;
    check(values);
  }
}
