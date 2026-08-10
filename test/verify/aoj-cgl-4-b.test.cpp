// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
// clang-format on
// competitive-verifier: ERROR 0.00000001

#include <complex>
#include <iomanip>
#include <iostream>

#include "../../geometry/convex_polygon_diameter.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int N;
  cin >> N;
  Polygon p(N);
  for (int i = 0; i < N; i++) {
    cin >> p[i];
  }
  auto ret = convex_polygon_diameter(p);
  cout << abs(p[ret.first] - p[ret.second]) << "\n";
}
