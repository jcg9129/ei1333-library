// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/largest-rectangle.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> h(N);
  for (int& height : h) cin >> height;
  cout << largest_rectangle(h) << endl;
}
