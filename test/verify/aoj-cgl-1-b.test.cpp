// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
// clang-format on
// competitive-verifier: ERROR 0.00000001

#include <iomanip>
#include <iostream>

#include "../../geometry/reflection.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  Line l;
  cin >> l;
  int Q;
  cin >> Q;
  while (Q--) {
    Point p;
    cin >> p;
    cout << reflection(l, p) << "\n";
  }
}
