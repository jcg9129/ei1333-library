// competitive-verifier: PROBLEM
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0233

#include <iostream>

#include "../../math/number-theory/convert-base.hpp"

using namespace std;

int main() {
  for (;;) {
    int X;
    cin >> X;
    if (X == 0) break;
    auto ret = convert_base(X, -10);
    for (auto& p : ret) cout << p;
    cout << endl;
  }
}
