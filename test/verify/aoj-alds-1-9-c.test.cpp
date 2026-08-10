// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C
// clang-format on

#include <iostream>
#include <string>

#include "../../structure/heap/leftist-heap.hpp"

using namespace std;

int main() {
  string s;
  LeftistHeap<int, false> que;
  auto root = que.make_root();
  while (cin >> s, s != "end") {
    if (s == "insert") {
      int x;
      cin >> x;
      root = que.push(root, x);
    } else {
      cout << root->key << "\n";
      root = que.pop(root);
    }
  }
}
