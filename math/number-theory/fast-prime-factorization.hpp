#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>

namespace FastPrimeFactorization {

template <typename word, typename dword, typename sword>
struct UnsafeMod {
  UnsafeMod() : x(0) {}

  UnsafeMod(word _x) : x(init(_x)) {}

  bool operator==(const UnsafeMod& rhs) const { return x == rhs.x; }

  bool operator!=(const UnsafeMod& rhs) const { return x != rhs.x; }

  UnsafeMod& operator+=(const UnsafeMod& rhs) {
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }

  UnsafeMod& operator-=(const UnsafeMod& rhs) {
    if (sword(x -= rhs.x) < 0) x += mod;
    return *this;
  }

  UnsafeMod& operator*=(const UnsafeMod& rhs) {
    x = reduce(dword(x) * rhs.x);
    return *this;
  }

  UnsafeMod operator+(const UnsafeMod& rhs) const {
    return UnsafeMod(*this) += rhs;
  }

  UnsafeMod operator-(const UnsafeMod& rhs) const {
    return UnsafeMod(*this) -= rhs;
  }

  UnsafeMod operator*(const UnsafeMod& rhs) const {
    return UnsafeMod(*this) *= rhs;
  }

  UnsafeMod pow(std::uint64_t e) const {
    UnsafeMod ret(1);
    for (UnsafeMod base = *this; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }
    return ret;
  }

  word get() const { return reduce(x); }

  static constexpr int word_bits = sizeof(word) * 8;

  static word modulus() { return mod; }

  static word init(word w) { return reduce(dword(w) * r2); }

  static void set_mod(word m) {
    mod = m;
    inv = mul_inv(mod);
    r2 = -dword(mod) % mod;
  }

  static word reduce(dword x) {
    word y =
        word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
  }

  static word mul_inv(word n, int e = 6, word x = 1) {
    return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }

  static word mod, inv, r2;

  word x;
};

using uint128_t = __uint128_t;

using Mod64 = UnsafeMod<std::uint64_t, uint128_t, std::int64_t>;
template <>
std::uint64_t Mod64::mod = 0;
template <>
std::uint64_t Mod64::inv = 0;
template <>
std::uint64_t Mod64::r2 = 0;

using Mod32 = UnsafeMod<std::uint32_t, std::uint64_t, std::int32_t>;
template <>
std::uint32_t Mod32::mod = 0;
template <>
std::uint32_t Mod32::inv = 0;
template <>
std::uint32_t Mod32::r2 = 0;

bool miller_rabin_primality_test_uint64(std::uint64_t n) {
  Mod64::set_mod(n);
  std::uint64_t d = n - 1;
  while (d % 2 == 0) d /= 2;
  Mod64 e{1}, rev{n - 1};
  // http://miller-rabin.appspot.com/  < 2^64
  for (std::uint64_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    if (n <= a) break;
    std::uint64_t t = d;
    Mod64 y = Mod64(a).pow(t);
    while (t != n - 1 && y != e && y != rev) {
      y *= y;
      t *= 2;
    }
    if (y != rev && t % 2 == 0) return false;
  }
  return true;
}

bool miller_rabin_primality_test_uint32(std::uint32_t n) {
  Mod32::set_mod(n);
  std::uint32_t d = n - 1;
  while (d % 2 == 0) d /= 2;
  Mod32 e{1}, rev{n - 1};
  for (std::uint32_t a : {2, 7, 61}) {
    if (n <= a) break;
    std::uint32_t t = d;
    Mod32 y = Mod32(a).pow(t);
    while (t != n - 1 && y != e && y != rev) {
      y *= y;
      t *= 2;
    }
    if (y != rev && t % 2 == 0) return false;
  }
  return true;
}

bool is_prime(std::uint64_t n) {
  if (n == 2) return true;
  if (n == 1 || n % 2 == 0) return false;
  if (n < std::uint64_t(1) << 31) return miller_rabin_primality_test_uint32(n);
  return miller_rabin_primality_test_uint64(n);
}

std::uint64_t pollard_rho(std::uint64_t n) {
  if (is_prime(n)) return n;
  if (n % 2 == 0) return 2;
  Mod64::set_mod(n);
  std::uint64_t d;
  Mod64 one{1};
  for (Mod64 c{one};; c += one) {
    Mod64 x{2}, y{2};
    do {
      x = x * x + c;
      y = y * y + c;
      y = y * y + c;
      d = std::gcd((x - y).get(), n);
    } while (d == 1);
    if (d < n) return d;
  }
  assert(0);
}

std::vector<std::uint64_t> prime_factor(std::uint64_t n) {
  if (n <= 1) return {};
  std::uint64_t p = pollard_rho(n);
  if (p == n) return {p};
  auto l = prime_factor(p);
  auto r = prime_factor(n / p);
  std::copy(r.begin(), r.end(), std::back_inserter(l));
  return l;
}
};  // namespace FastPrimeFactorization
