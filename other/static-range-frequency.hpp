#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

template <typename T>
struct StaticRangeFrequency {
 private:
  std::vector<T> vs;
  std::vector<std::vector<int> > mp;

 public:
  explicit StaticRangeFrequency(const std::vector<T>& xs) : vs{xs} {
    std::sort(vs.begin(), vs.end());
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    mp.resize(vs.size());
    for (int i = 0; i < xs.size(); i++) {
      int p = std::lower_bound(vs.begin(), vs.end(), xs[i]) - vs.begin();
      mp[p].emplace_back(i);
    }
  }
  std::size_t query(int l, int r, T x) const {
    int p = std::lower_bound(vs.begin(), vs.end(), x) - vs.begin();
    if (p == (int)vs.size() or x != vs[p]) return 0;
    l = std::lower_bound(mp[p].begin(), mp[p].end(), l) - mp[p].begin();
    r = std::lower_bound(mp[p].begin(), mp[p].end(), r) - mp[p].begin();
    return r - l;
  }
};
