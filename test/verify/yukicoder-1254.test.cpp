// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1254

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../graph/others/namori-graph.hpp"

using namespace std;

int main() {
  int N;
  cin >> N;
  NamoriGraph<int> g(N);
  g.read(N);
  g.build();
  vector<int> ans;
  for (auto& e : g.loop_edges) {
    ans.emplace_back(e.idx + 1);
  }
  sort(begin(ans), end(ans));
  cout << ans.size() << "\n";
  for (int i = 0; i < static_cast<int>(ans.size()); ++i) {
    if (i) cout << ' ';
    cout << ans[i];
  }
  cout << '\n';
}
