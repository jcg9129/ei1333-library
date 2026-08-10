// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
// clang-format on

#include <iomanip>
#include <iostream>

#include "../../geometry/is_intersect_ss.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int T;
  cin >> T;
  while (T--) {
    Segment a, b;
    cin >> a >> b;
    cout << is_intersect_ss(a, b) << "\n";
  }
}
