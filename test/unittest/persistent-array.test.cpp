// competitive-verifier: STANDALONE

#include "../../structure/others/persistent-array.hpp"

#include <cassert>
#include <vector>

int main() {
  PersistentArray<int, 2> original;
  original.build(std::vector<int>{10, 20, 30, 40, 50});
  assert(original.get(0) == 10);
  assert(original.get(4) == 50);

  auto first = original;
  *first.mutable_get(1) = 200;
  *first.mutable_get(4) = 500;
  assert(original.get(1) == 20);
  assert(original.get(4) == 50);
  assert(first.get(1) == 200);
  assert(first.get(4) == 500);

  auto second = first;
  *second.mutable_get(0) = -1;
  assert(first.get(0) == 10);
  assert(second.get(0) == -1);
}
