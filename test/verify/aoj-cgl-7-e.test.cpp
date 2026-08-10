// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
// clang-format on
// competitive-verifier: ERROR 0.000001

#include <iomanip>
#include <iostream>
#include <utility>

#include "../../geometry/cross_point_cc.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  Circle x, y;
  cin >> x.p >> x.r >> y.p >> y.r;
  auto ret = cross_point_cc(x, y);
  if (ret.size() == 1) ret.emplace_back(ret[0]);
  if (!compare_x(ret[0], ret[1])) swap(ret[0], ret[1]);
  cout << ret[0] << " " << ret[1] << "\n";
}
