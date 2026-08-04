// competitive-verifier: STANDALONE

#include "../../structure/others/plus-minus-one-rmq.hpp"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

void check(const std::vector<int>& values) {
  const PlusMinusOneRMQ<int> rmq(values);
  for (int left = 0; left < (int)values.size(); left++) {
    int expected = values[left];
    for (int right = left + 1; right <= (int)values.size(); right++) {
      expected = std::min(expected, values[right - 1]);
      const auto [value, position] = rmq.fold(left, right);
      assert(value == expected);
      assert(left <= position && position < right);
      assert(values[position] == value);
    }
  }
}

int main() {
  check({42});
  check({0, 1, 0, -1, 0, -1, -2, -1});

  std::mt19937 rng(123456789);
  for (int n = 1; n <= 100; n++) {
    std::vector<int> values(n);
    values[0] = (int)(rng() % 101) - 50;
    for (int i = 1; i < n; i++) {
      values[i] = values[i - 1] + (rng() % 2 == 0 ? -1 : 1);
    }
    check(values);
  }
}
