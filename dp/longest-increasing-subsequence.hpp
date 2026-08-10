#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

template <typename T>
std::size_t longest_increasing_subsequence(const std::vector<T>& a,
                                           bool strict) {
  std::vector<T> lis;
  for (auto& p : a) {
    typename std::vector<T>::iterator it;
    if (strict)
      it = std::lower_bound(lis.begin(), lis.end(), p);
    else
      it = std::upper_bound(lis.begin(), lis.end(), p);
    if (lis.end() == it)
      lis.emplace_back(p);
    else
      *it = p;
  }
  return lis.size();
}
