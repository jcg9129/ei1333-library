// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C
// clang-format on
// competitive-verifier: ERROR 0.00000001

#include <iomanip>
#include <iostream>

#include "../../geometry/cross_point_ll.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int T;
  cin >> T;
  while (T--) {
    Line a, b;
    cin >> a >> b;
    cout << cross_point_ll(a, b) << "\n";
  }
}
