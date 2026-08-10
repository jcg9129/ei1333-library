#pragma once

#include <cstdint>

constexpr std::uint64_t CYCLES_PER_SEC = 2900000000;  // AtCoder
// constexpr std::uint64_t CYCLES_PER_SEC = 3600000000; // Codeforces
// constexpr std::uint64_t CYCLES_PER_SEC = 2300000000; // yukicoder
struct Timer {
  std::uint64_t start;

  Timer() : start{} { reset(); }

  void reset() { start = get_cycle(); }

  inline double get_second() const {
    return (double)get_cycle() / CYCLES_PER_SEC;
  }

  inline std::uint64_t get_cycle() const {
    unsigned low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return (((std::uint64_t)low) | ((std::uint64_t)high << 32ull)) - start;
  }
};
