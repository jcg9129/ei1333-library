// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings
// clang-format on

#include <iostream>
#include <numeric>
#include <string>

#include "../../string/lcp-array.hpp"

using namespace std;

int main() {
  string S;
  cin >> S;
  int N = static_cast<int>(S.size());
  SuffixArray sa(S);
  auto lcp = lcp_array(sa);
  cout << 1LL * N * (N + 1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL)
       << "\n";
}
