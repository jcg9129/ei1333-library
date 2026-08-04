// competitive-verifier: STANDALONE

#include <cassert>
#include <queue>
#include <random>
#include <vector>

#include "../../structure/heap/erasable-heap.hpp"
#include "../../structure/heap/leftist-heap.hpp"
#include "../../structure/heap/persistent-leftist-heap.hpp"
#include "../../structure/heap/skew-heap.hpp"

int main() {
  {
    erasable_heap<int> heap;
    heap.push(3);
    heap.push(1);
    heap.push(5);
    heap.push(5);
    assert(heap.top() == 5);
    heap.erase(5);
    assert(heap.top() == 5);
    heap.pop();
    assert(heap.top() == 3);
    heap.erase(1);
    heap.pop();
    assert(heap.empty());
  }

  {
    LeftistHeap<int> heap;
    auto root = heap.make_root();
    std::priority_queue<int, std::vector<int>, std::greater<int>> expected;
    std::mt19937 rng(123456789);
    for (int iteration = 0; iteration < 5000; iteration++) {
      if (expected.empty() || rng() % 3 != 0) {
        int value = (int)(rng() % 201) - 100;
        root = heap.push(root, value);
        expected.push(value);
      } else {
        assert(root->key == expected.top());
        root = heap.pop(root);
        expected.pop();
      }
      if (!expected.empty()) assert(root->key == expected.top());
    }
  }

  {
    PersistentLeftistHeap<int> heap;
    auto base = heap.make_root();
    base = heap.push(base, 3);
    base = heap.push(base, 7);
    auto first = heap.push(base, 1);
    auto second = heap.push(base, 5);
    assert(base->key == 3);
    assert(first->key == 1);
    assert(second->key == 3);
    second = heap.pop(second);
    assert(second->key == 5);
    assert(base->key == 3);
  }

  {
    SkewHeap<long long> heap;
    auto root = heap.make_root();
    root = heap.push(root, 5);
    root = heap.push(root, 2);
    root = heap.push(root, 8);
    assert(root->key == 2);
    root = heap.add(root, 10);
    assert(root->key == 12);
    root = heap.pop(root);
    assert(root->key == 15);
  }
}
