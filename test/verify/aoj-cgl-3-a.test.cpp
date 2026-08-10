// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
// clang-format on

#include <iomanip>
#include <iostream>

#include "../../geometry/area.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int N;
  cin >> N;
  Polygon p(N);
  for (auto& s : p) cin >> s;
  cout << fixed << setprecision(1) << area(p) << "\n";
}
