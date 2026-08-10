// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
// clang-format on

#include <iostream>
#include <string>

#include "../../string/suffix-array.hpp"

using namespace std;

int main() {
  string S;
  int Q;

  cin >> S;
  SuffixArray sa(S);
  cin >> Q;
  while (Q--) {
    string T;
    cin >> T;
    auto range = sa.equal_range(T);
    cout << (range.first != range.second) << endl;
  }
}
