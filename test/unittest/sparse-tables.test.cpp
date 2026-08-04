// competitive-verifier: STANDALONE

#include <algorithm>
#include <cassert>
#include <functional>
#include <random>
#include <vector>

#include "../../structure/others/disjoint-sparse-table.hpp"
#include "../../structure/others/sparse-table.hpp"

int main() {
  {
    const std::vector<int> values{5, 2, 7, 1, 6};
    const auto table =
        get_sparse_table(values, [](int a, int b) { return std::min(a, b); });
    assert(table.fold(0, 1) == 5);
    assert(table.fold(1, 4) == 1);
    assert(table.fold(0, 5) == 1);
  }

  {
    const std::vector<int> values{42};
    auto table = get_disjoint_sparse_table(values, std::plus<int>());
    assert(table.fold(0, 1) == 42);
  }

  std::mt19937 rng(123456789);
  for (int n = 1; n <= 50; n++) {
    std::vector<int> values(n);
    for (int& value : values) value = (int)(rng() % 201) - 100;

    const auto minimum =
        get_sparse_table(values, [](int a, int b) { return std::min(a, b); });
    auto sum = get_disjoint_sparse_table(values, std::plus<int>());
    for (int left = 0; left < n; left++) {
      int expected_minimum = values[left];
      int expected_sum = 0;
      for (int right = left + 1; right <= n; right++) {
        expected_minimum = std::min(expected_minimum, values[right - 1]);
        expected_sum += values[right - 1];
        assert(minimum.fold(left, right) == expected_minimum);
        assert(sum.fold(left, right) == expected_sum);
      }
    }
  }
}
