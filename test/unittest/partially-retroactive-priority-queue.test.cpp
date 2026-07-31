// competitive-verifier: STANDALONE

#include "../../template/template.hpp"

#include "../../structure/heap/partially-retroactive-priority-queue.hpp"

namespace {

enum class OperationType { NOOP, PUSH, POP };

struct Operation {
  OperationType type = OperationType::NOOP;
  long long value = 0;
};

template <typename Compare>
struct NaivePriorityQueue {
  multiset<long long, Compare> values;
  long long sum = 0;
};

template <typename Compare>
NaivePriorityQueue<Compare> build_naive(const vector<Operation>& operations,
                                        Compare compare) {
  NaivePriorityQueue<Compare> ret{multiset<long long, Compare>(compare), 0};
  for (const auto& operation : operations) {
    if (operation.type == OperationType::PUSH) {
      ret.values.insert(operation.value);
      ret.sum += operation.value;
    } else if (operation.type == OperationType::POP and
               not ret.values.empty()) {
      ret.sum -= *ret.values.begin();
      ret.values.erase(ret.values.begin());
    }
  }
  return ret;
}

template <typename Compare>
void check(const PartiallyRetroactivePriorityQueue<long long, Compare>& queue,
           const vector<Operation>& operations, Compare compare) {
  auto expected = build_naive(operations, compare);
  assert(queue.empty() == expected.values.empty());
  assert(queue.size() == (int)expected.values.size());
  assert(queue.sum() == expected.sum);
  if (not expected.values.empty()) {
    assert(queue.top() == *expected.values.begin());
  }
}

template <typename Compare>
void exhaustive_test(Compare compare) {
  constexpr int N = 6;
  constexpr int STATES = 5;
  int patterns = 1;
  for (int i = 0; i < N; i++) patterns *= STATES;

  for (int mask = 0; mask < patterns; mask++) {
    PartiallyRetroactivePriorityQueue<long long, Compare> queue(N, compare);
    vector<Operation> operations(N);
    int x = mask;
    for (int t = 0; t < N; t++) {
      int state = x % STATES;
      x /= STATES;
      if (state == 1) {
        operations[t].type = OperationType::POP;
        queue.set_pop(t);
      } else if (state >= 2) {
        operations[t] = {OperationType::PUSH, state - 3};
        queue.set_push(t, state - 3);
      }
    }
    check(queue, operations, compare);
  }
}

template <typename Compare>
void random_test(Compare compare, uint64_t seed) {
  mt19937_64 rng(seed);
  for (int n = 1; n <= 30; n++) {
    for (int rep = 0; rep < 100; rep++) {
      PartiallyRetroactivePriorityQueue<long long, Compare> queue(n, compare);
      vector<Operation> operations(n);
      check(queue, operations, compare);

      for (int q = 0; q < 300; q++) {
        int t = (int)(rng() % n);
        int type = (int)(rng() % 3);
        if (type == 0) {
          long long value = (long long)(rng() % 21) - 10;
          operations[t] = {OperationType::PUSH, value};
          queue.set_push(t, value);
        } else if (type == 1) {
          operations[t] = {OperationType::POP, 0};
          queue.set_pop(t);
        } else {
          operations[t] = {};
          queue.set_noop(t);
        }
        check(queue, operations, compare);
      }
    }
  }
}

}  // namespace

int main() {
  {
    PartiallyRetroactivePriorityQueue<long long> queue(0);
    assert(queue.empty());
    assert(queue.size() == 0);
    assert(queue.sum() == 0);
  }
  {
    PartiallyRetroactivePriorityQueue<long long> queue(6);
    queue.set_pop(0);
    queue.set_push(1, 4);
    queue.set_pop(2);
    queue.set_push(3, 2);
    queue.set_push(4, 2);
    assert(queue.size() == 2);
    assert(queue.top() == 2);
    assert(queue.sum() == 4);

    queue.set_noop(0);
    assert(queue.size() == 2);
    assert(queue.sum() == 4);

    queue.set_noop(2);
    assert(queue.size() == 3);
    assert(queue.top() == 2);
    assert(queue.sum() == 8);

    queue.set_pop(5);
    assert(queue.size() == 2);
    assert(queue.top() == 2);
    assert(queue.sum() == 6);

    queue.set_push(3, -5);
    assert(queue.size() == 2);
    assert(queue.top() == 2);
    assert(queue.sum() == 6);
  }

  exhaustive_test(less<long long>());
  exhaustive_test(greater<long long>());
  random_test(less<long long>(), 123456789);
  random_test(greater<long long>(), 987654321);
}
