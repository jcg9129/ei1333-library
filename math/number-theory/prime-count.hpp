#pragma once

#include <cstdint>
#include <vector>

#include "kth-root-integer.hpp"
#include "prime-table.hpp"

/**
 * @brief Prime Count(素数の個数)
 */
template <std::int64_t LIM = 100000000000LL>
struct PrimeCount {
 private:
  std::int64_t sq;
  std::vector<bool> prime;
  std::vector<std::int64_t> prime_sum, primes;

  std::int64_t p2(std::int64_t x, std::int64_t y) {
    if (x < 4) return 0;
    std::int64_t a = pi(y);
    std::int64_t b = pi(kth_root_integer(x, 2));
    if (a >= b) return 0;
    std::int64_t sum = (a - 2) * (a + 1) / 2 - (b - 2) * (b + 1) / 2;
    for (std::int64_t i = a; i < b; i++) sum += pi(x / primes[i]);
    return sum;
  }

  std::int64_t phi(std::int64_t m, std::int64_t n) {
    if (m < 1) return 0;
    if (n > m) return 1;
    if (n < 1) return m;
    if (m <= primes[n - 1] * primes[n - 1]) return pi(m) - n + 1;
    if (m <= primes[n - 1] * primes[n - 1] * primes[n - 1] && m <= sq) {
      std::int64_t sx = pi(kth_root_integer(m, 2));
      std::int64_t ans = pi(m) - (sx + n - 2) * (sx - n + 1) / 2;
      for (std::int64_t i = n; i < sx; ++i) ans += pi(m / primes[i]);
      return ans;
    }
    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
  }

 public:
  PrimeCount() : sq(kth_root_integer(LIM, 2)), prime_sum(sq + 1) {
    prime = prime_table(sq);
    for (int i = 1; i <= sq; i++) prime_sum[i] = prime_sum[i - 1] + prime[i];
    primes.reserve(prime_sum[sq]);
    for (int i = 1; i <= sq; i++)
      if (prime[i]) primes.push_back(i);
  }

  std::int64_t pi(std::int64_t n) {
    if (n <= sq) return prime_sum[n];
    std::int64_t m = kth_root_integer(n, 3);
    std::int64_t a = pi(m);
    return phi(n, a) + a - 1 - p2(n, m);
  }
};
