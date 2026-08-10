// clang-format off
// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
// clang-format on

#include <iomanip>
#include <iostream>

#include "../../geometry/is_orthogonal.hpp"
#include "../../geometry/is_parallel.hpp"

using namespace std;
using namespace geometry;

int main() {
  cout << fixed << setprecision(10);
  int Q;
  cin >> Q;
  while (Q--) {
    Line s1, s2;
    cin >> s1 >> s2;
    if (is_parallel(s1, s2))
      cout << "2\n";
    else if (is_orthogonal(s1, s2))
      cout << "1\n";
    else
      cout << "0\n";
  }
}
