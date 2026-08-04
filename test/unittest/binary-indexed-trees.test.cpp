// competitive-verifier: STANDALONE

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#include "../../structure/others/abstract-binary-indexed-tree.hpp"
#include "../../structure/others/binary-indexed-tree.hpp"

int main() {
  {
    BinaryIndexedTree<int> tree(std::vector<int>{1, 2, 3, 4});
    assert(tree.prod(0) == 0);
    assert(tree.prod(4) == 10);
    assert(tree.prod(1, 3) == 5);
    assert(tree.lower_bound(1) == 0);
    assert(tree.lower_bound(4) == 2);
    assert(tree.lower_bound(11) == 4);
    assert(tree.upper_bound(0) == 0);
    assert(tree.upper_bound(3) == 2);
    assert(tree.upper_bound(10) == 4);
  }

  std::mt19937 rng(123456789);
  for (int n = 1; n <= 100; n++) {
    std::vector<int> values(n);
    BinaryIndexedTree<int> sum(n);
    for (int iteration = 0; iteration < 500; iteration++) {
      int index = rng() % n;
      int delta = rng() % 10;
      values[index] += delta;
      sum.apply(index, delta);

      int left = rng() % (n + 1);
      int right = rng() % (n + 1);
      if (left > right) std::swap(left, right);
      int expected = 0;
      for (int i = left; i < right; i++) expected += values[i];
      assert(sum.prod(left, right) == expected);
    }

    auto maximum = get_abstract_binary_indexed_tree(
        values, [](int a, int b) { return std::max(a, b); }, -1);
    int expected = -1;
    for (int right = 0; right <= n; right++) {
      if (right > 0) expected = std::max(expected, values[right - 1]);
      assert(maximum.prod(right) == expected);
    }
  }
}
