// competitive-verifier: STANDALONE

#include "../../structure/others/priority-sum-structure.hpp"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

int main() {
  MaximumSum<long long> maximum(0);
  MinimumSum<long long> minimum(0);
  std::vector<long long> values;
  std::mt19937 rng(123456789);

  for (int iteration = 0; iteration < 5000; iteration++) {
    if (values.empty() || rng() % 3 != 0) {
      long long value = (int)(rng() % 201) - 100;
      values.push_back(value);
      maximum.insert(value);
      minimum.insert(value);
    } else {
      int index = rng() % values.size();
      maximum.erase(values[index]);
      minimum.erase(values[index]);
      values.erase(values.begin() + index);
    }

    std::sort(values.begin(), values.end());
    std::size_t k = values.empty() ? 0 : rng() % (values.size() + 1);
    maximum.set_k(k);
    minimum.set_k(k);

    long long expected_minimum = 0;
    long long expected_maximum = 0;
    for (std::size_t i = 0; i < k; i++) {
      expected_minimum += values[i];
      expected_maximum += values[values.size() - 1 - i];
    }
    assert(minimum.query() == expected_minimum);
    assert(maximum.query() == expected_maximum);
    assert(minimum.size() == values.size());
    assert(maximum.size() == values.size());
    if (k > 0) {
      assert(minimum.kth_element() == values[k - 1]);
      assert(maximum.kth_element() == values[values.size() - k]);
    }
  }
}
