// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E
// clang-format on

#include <iostream>
#include <string>

#include "../../dp/edit-distance.hpp"

using namespace std;

int main() {
  string S, T;
  cin >> S >> T;
  cout << edit_distance(S, T) << endl;
}
