#pragma once

#include <type_traits>

template <typename T>
T ceil_div(T n, T d) {
  static_assert(std::is_integral<T>::value and std::is_signed<T>::value,
                "template parameter T must be signed integral type");
  return n / d + ((n ^ d) >= 0 && n % d != 0);
}
