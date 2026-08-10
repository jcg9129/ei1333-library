// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1826

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

#include "../../structure/others/abstract-2d-binary-indexed-tree-compressed.hpp"

using namespace std;

constexpr int64_t kNegativeInfinity = -(int64_t{1} << 60);

int main() {
  int N;
  cin >> N;
  vector<tuple<int, int, int> > ds;
  ds.reserve(N + 1);
  for (int i = 0; i < N; i++) {
    int t, x, v;
    cin >> t >> x >> v;
    ds.emplace_back(t, x, v);
  }
  ds.emplace_back(0, 0, 0);
  sort(begin(ds), end(ds));
  vector<int64_t> dp(ds.size(), kNegativeInfinity);
  dp[0] = 0;
  vector<int> l, r;
  vector<pair<int, int> > m;
  l.reserve(N + 1);
  r.reserve(N + 1);
  m.reserve(N + 1);
  int ptr = 0;
  for (auto& [t, x, v] : ds) {
    l.emplace_back(t + x);
    r.emplace_back(t - x);
    m.emplace_back(x, ptr++);
  }
  sort(begin(l), end(l));
  l.erase(unique(begin(l), end(l)), end(l));
  sort(begin(r), end(r));
  r.erase(unique(begin(r), end(r)), end(r));
  sort(begin(m), end(m));
  vector<int> ldx(ds.size()), rdx(ds.size()), mdx(ds.size());
  for (int i = 0; i < (int)ds.size(); i++) {
    auto [t, x, v] = ds[i];
    ldx[i] = lower_bound(begin(l), end(l), t + x) - begin(l);
    rdx[i] = lower_bound(begin(r), end(r), t - x) - begin(r);
    mdx[i] = lower_bound(begin(m), end(m), make_pair(x, i)) - begin(m);
  }
  auto f = [](int64_t a, int64_t b) { return max(a, b); };
  // みんなの2D segment tree

  vector<int> ladx(m.size()), radx(m.size());
  for (int i = 0; i < (int)ds.size(); i++) {
    ladx[m.size() - mdx[i] - 1] = ldx[i];
    radx[mdx[i]] = rdx[i];
  }
  auto lseg = get_abstract_2d_binary_indexed_tree_compressed(ladx, f,
                                                             kNegativeInfinity);
  auto rseg = get_abstract_2d_binary_indexed_tree_compressed(radx, f,
                                                             kNegativeInfinity);
  vector<int> ord(ds.size());
  lseg.apply(m.size() - mdx[0] - 1, 0);
  rseg.apply(mdx[0], 0);
  int64_t ret = 0;
  for (int i = 1; i < (int)ds.size(); i++) {
    auto [t2, x2, v2] = ds[i];
    auto v = max(lseg.prod(m.size() - mdx[i], ldx[i] + 1),
                 rseg.prod(mdx[i], rdx[i] + 1));
    v += v2;
    if (v >= 0) {
      ret = max(ret, v);
      lseg.apply(m.size() - mdx[i] - 1, v);
      rseg.apply(mdx[i], v);
    }
  }
  cout << ret << "\n";
}
