#pragma once

#include <algorithm>
#include <tuple>
#include <vector>

template <typename T>
std::vector<std::tuple<T, T, T> > enumerate_quotients(T n) {
  T l = 1;
  std::vector<std::tuple<T, T, T> > quotients;
  while (l <= n) {
    T q = n / l;
    T r = n / q + 1;
    quotients.emplace_back(q, l, r);
    l = r;
  }
  reverse(quotients.begin(), quotients.end());
  return quotients;
}
