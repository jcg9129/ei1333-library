// competitive-verifier: STANDALONE

#include <cassert>
#include <deque>
#include <random>
#include <string>

#include "../../structure/others/deque-operate-aggregation.hpp"
#include "../../structure/others/queue-operate-aggregation.hpp"

std::string naive_product(const std::deque<std::string>& values) {
  std::string result;
  for (const auto& value : values) result += value;
  return result;
}

int main() {
  const auto concatenate = [](const std::string& a, const std::string& b) {
    return a + b;
  };
  {
    auto queue = get_queue_operate_aggregation<std::string>(concatenate);
    assert(queue.empty());
    queue.push("a");
    queue.push("bc");
    assert(queue.size() == 2);
    assert(queue.all_prod() == "abc");
    queue.pop();
    assert(queue.all_prod() == "bc");
    queue.pop();
    assert(queue.empty());
  }

  auto deque = get_deque_operate_aggregation<std::string>(concatenate);
  std::deque<std::string> expected;
  std::mt19937 rng(123456789);
  for (int iteration = 0; iteration < 5000; iteration++) {
    int operation = expected.empty() ? rng() % 2 : rng() % 4;
    if (operation == 0) {
      std::string value(1, (char)('a' + rng() % 26));
      deque.push_front(value);
      expected.push_front(value);
    } else if (operation == 1) {
      std::string value(1, (char)('a' + rng() % 26));
      deque.push_back(value);
      expected.push_back(value);
    } else if (operation == 2) {
      deque.pop_front();
      expected.pop_front();
    } else {
      deque.pop_back();
      expected.pop_back();
    }

    assert(deque.empty() == expected.empty());
    assert(deque.size() == expected.size());
    if (!expected.empty()) assert(deque.all_prod() == naive_product(expected));
  }
}
