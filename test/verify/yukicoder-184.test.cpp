// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/184

#include <cstdint>
#include <iostream>

#include "../../math/matrix/binary-basis.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  BinaryBasis<int64_t> bb;
  for (int i = 0; i < N; i++) {
    int64_t x;
    cin >> x;
    bb.add(x);
  }
  cout << (1LL << bb.size()) << "\n";
}
