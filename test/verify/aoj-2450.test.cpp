// competitive-verifier: PROBLEM
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "../../structure/segment-tree/lazy-segment-tree.hpp"

#include "../../graph/tree/heavy-light-decomposition.hpp"

using namespace std;

constexpr int64_t kInfinity = numeric_limits<int64_t>::max();

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> S(N);
  for (int i = 0; i < N; i++) {
    cin >> S[i];
  }
  HeavyLightDecomposition<int64_t> tree(N);
  tree.read(N - 1);
  tree.build();

  struct Node {
    int64_t ans, all, left, right, length;

    Node()
        : ans(-kInfinity),
          all(0),
          left(-kInfinity),
          right(-kInfinity),
          length(0) {}

    Node(int64_t val, int64_t len) {
      length = len;
      all = val * length;
      ans = left = right = (val > 0 ? all : val);
    }

    Node operator+(const Node& s) const {
      Node ret;
      ret.length = length + s.length;
      ret.ans = max({ans, s.ans, right + s.left});
      ret.all = all + s.all;
      ret.left = max(left, all + s.left);
      ret.right = max(s.right, right + s.all);
      return ret;
    }
  };
  auto F = [](const Node& a, const Node& b) { return a + b; };
  auto G = [](const Node& x, int64_t f) -> Node { return {f, x.length}; };
  auto H = [](int64_t f, int64_t g) { return g; };
  auto e = []() { return Node(); };
  auto id = []() { return kInfinity; };

  vector<Node> vs(N);
  for (int i = 0; i < N; i++) vs[i] = {S[tree.rev[i]], 1};
  LazySegmentTree seg(LambdaActedMonoid(F, e, G, H, id), vs);

  auto QF = [&](int a, int b) { return seg.prod(a, b); };
  auto QG = [](const Node& a, const Node& b) { return a + b; };
  auto QS = [](Node l, const Node& r) {
    swap(l.left, l.right);
    return l + r;
  };

  while (Q--) {
    int T, A, B, C;
    cin >> T >> A >> B >> C;
    --A, --B;
    if (T == 1) {
      tree.add(A, B, [&](int a, int b) { seg.apply(a, b, C); });
    } else {
      cout << tree.query(A, B, Node(), QF, QG, QS).ans << "\n";
    }
  }
}
