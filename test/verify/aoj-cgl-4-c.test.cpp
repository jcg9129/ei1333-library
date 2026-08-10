// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
// clang-format on
// competitive-verifier: ERROR 0.00001

#include <iomanip>
#include <iostream>

#include "../../geometry/area.hpp"
#include "../../geometry/convex_polygon_cut.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int n;
  cin >> n;
  Polygon poly(n);
  for (auto& p : poly) {
    cin >> p;
  }
  int q;
  cin >> q;
  while (q--) {
    Line l;
    cin >> l;
    cout << area(convex_polygon_cut(poly, l)) << "\n";
  }
}
