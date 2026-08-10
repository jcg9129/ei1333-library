// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
// clang-format on

#include <iomanip>
#include <iostream>

#include "../../geometry/is_convex_polygon.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int N;
  cin >> N;
  Polygon p(N);
  for (auto& s : p) cin >> s;
  cout << is_convex_polygon(p) << endl;
}
