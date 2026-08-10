// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
// clang-format on

#include <iostream>

#include "../../structure/trie/binary-trie.hpp"

int main() {
  int N, Q;
  std::cin >> N >> Q;
  BinaryTrie<int, 20> bt;
  for (int i = 0; i < Q; i++) {
    int c, x, y;
    std::cin >> c >> x >> y;
    if (c == 0) {
      bt.add(x, -1, y);
    } else if (c == 1) {
      std::cout << bt.count_less(y + 1) - bt.count_less(x) << "\n";
    }
  }
}
