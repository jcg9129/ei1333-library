#pragma once

#include "../class/range-add-range-min.hpp"
#include "../segment-tree/lazy-segment-tree.hpp"

template <typename T, typename Compare = std::less<T> >
struct PartiallyRetroactivePriorityQueue {
 private:
  enum class OperationType : uint8_t { NOOP, PUSH, POP };

  struct Operation {
    OperationType type = OperationType::NOOP;
    optional<T> value;
    bool alive = false;
  };

  struct CandidateNode {
    int alive_min = -1;
    int deleted_max = -1;
  };

  int n;
  int operation_count;
  int seg_size;
  Compare compare;

  vector<Operation> operations;
  vector<CandidateNode> candidates;
  // A deleted push has weight +1, a surviving push has weight 0, and a pop
  // has weight -1. Their prefix sums are nonnegative, and a zero is a bridge.
  // Updating one operation is a suffix addition on the prefix-sum array.
  LazySegmentTree<RangeAddRangeMin<int> > prefix;

  // A batch of n virtual values with lower priority than every real value is
  // inserted before the timeline. It makes every pop valid; popping one of
  // them is exactly an ignored pop on an empty real queue.
  int dummy_alive;
  int dummy_deleted = 0;

  int present_size = 0;
  T present_sum{};

  bool key_less(int a, int b) const {
    assert(a >= 0 and b >= 0);
    if (a == b) return false;
    if (a == 0) return false;
    if (b == 0) return true;
    const T& x = *operations[a - 1].value;
    const T& y = *operations[b - 1].value;
    if (compare(x, y)) return true;
    if (compare(y, x)) return false;
    return a < b;
  }

  int min_id(int a, int b) const {
    if (a == -1) return b;
    if (b == -1) return a;
    return key_less(a, b) ? a : b;
  }

  int max_id(int a, int b) const {
    if (a == -1) return b;
    if (b == -1) return a;
    return key_less(a, b) ? b : a;
  }

  void pull_candidate(int k) {
    candidates[k].alive_min =
        min_id(candidates[2 * k].alive_min, candidates[2 * k + 1].alive_min);
    candidates[k].deleted_max = max_id(candidates[2 * k].deleted_max,
                                       candidates[2 * k + 1].deleted_max);
  }

  void refresh_candidate(int p) {
    CandidateNode node;
    if (p == 0) {
      if (dummy_alive > 0) node.alive_min = 0;
      if (dummy_deleted > 0) node.deleted_max = 0;
    } else {
      const auto& op = operations[p - 1];
      if (op.type == OperationType::PUSH) {
        if (op.alive) {
          node.alive_min = p;
        } else {
          node.deleted_max = p;
        }
      }
    }
    int k = p + seg_size;
    candidates[k] = node;
    while (k >>= 1) pull_candidate(k);
  }

  int range_min_alive(int l, int r) const {
    int ret = -1;
    for (l += seg_size, r += seg_size; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret = min_id(ret, candidates[l++].alive_min);
      if (r & 1) ret = min_id(ret, candidates[--r].alive_min);
    }
    assert(ret != -1);
    return ret;
  }

  int range_max_deleted(int l, int r) const {
    int ret = -1;
    for (l += seg_size, r += seg_size; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret = max_id(ret, candidates[l++].deleted_max);
      if (r & 1) ret = max_id(ret, candidates[--r].deleted_max);
    }
    assert(ret != -1);
    return ret;
  }

  void add_weight(int p, int x) { prefix.apply(p + 1, operation_count + 1, x); }

  int find_first_zero(int l) {
    auto ret = prefix.find_first(l, [](int x) { return x == 0; });
    assert(ret.has_value());
    return *ret - 1;
  }

  int find_last_zero(int r) {
    auto ret = prefix.find_last(r + 1, [](int x) { return x == 0; });
    assert(ret.has_value());
    return *ret;
  }

  void promote(int id) {
    if (id == 0) {
      assert(dummy_deleted > 0);
      --dummy_deleted;
      ++dummy_alive;
      add_weight(0, -1);
      refresh_candidate(0);
      return;
    }
    auto& op = operations[id - 1];
    assert(op.type == OperationType::PUSH and not op.alive);
    op.alive = true;
    add_weight(id, -1);
    ++present_size;
    present_sum += *op.value;
    refresh_candidate(id);
  }

  void demote(int id) {
    if (id == 0) {
      assert(dummy_alive > 0);
      --dummy_alive;
      ++dummy_deleted;
      add_weight(0, 1);
      refresh_candidate(0);
      return;
    }
    auto& op = operations[id - 1];
    assert(op.type == OperationType::PUSH and op.alive);
    op.alive = false;
    add_weight(id, 1);
    --present_size;
    present_sum -= *op.value;
    refresh_candidate(id);
  }

  void check_time(int t) const { assert(0 <= t and t < n); }

  static int checked_size(int size) {
    assert(size >= 0);
    return size;
  }

 public:
  explicit PartiallyRetroactivePriorityQueue(int size,
                                             Compare comparator = Compare())
      : n(checked_size(size)),
        operation_count(n + 1),
        seg_size(1),
        compare(std::move(comparator)),
        operations(n),
        prefix(RangeAddRangeMin<int>(), vector<int>(n + 2)),
        dummy_alive(n) {
    while (seg_size < operation_count) seg_size <<= 1;
    candidates.assign(2 * seg_size, CandidateNode{});
    refresh_candidate(0);
  }

  /** Replaces operation t by push(value). */
  void set_push(int t, T value) {
    check_time(t);
    set_noop(t);
    int p = t + 1;
    auto& op = operations[t];
    op.type = OperationType::PUSH;
    op.value.emplace(std::move(value));
    op.alive = false;
    add_weight(p, 1);
    refresh_candidate(p);

    int bridge = find_last_zero(p);
    promote(range_max_deleted(bridge, operation_count));
  }

  /** Replaces operation t by pop. It is ignored when the queue is empty. */
  void set_pop(int t) {
    check_time(t);
    set_noop(t);
    int p = t + 1;

    int bridge = find_first_zero(p + 1);
    demote(range_min_alive(0, bridge));

    auto& op = operations[t];
    op.type = OperationType::POP;
    op.value.reset();
    op.alive = false;
    add_weight(p, -1);
  }

  /** Replaces operation t by a no-op. */
  void set_noop(int t) {
    check_time(t);
    int p = t + 1;
    auto& op = operations[t];
    if (op.type == OperationType::NOOP) return;

    if (op.type == OperationType::POP) {
      int bridge = find_last_zero(p);
      int id = range_max_deleted(bridge, operation_count);
      add_weight(p, 1);
      promote(id);
    } else if (op.alive) {
      --present_size;
      present_sum -= *op.value;
    } else {
      int bridge = find_first_zero(p + 1);
      int id = range_min_alive(0, bridge);
      demote(id);
      add_weight(p, -1);
    }

    op.type = OperationType::NOOP;
    op.alive = false;
    refresh_candidate(p);
    op.value.reset();
  }

  bool empty() const { return present_size == 0; }

  int size() const { return present_size; }

  const T& top() const {
    assert(not empty());
    int id = candidates[1].alive_min;
    assert(id > 0);
    return *operations[id - 1].value;
  }

  T sum() const { return present_sum; }
};
