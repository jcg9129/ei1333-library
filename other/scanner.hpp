#pragma once

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

/**
 * @brief Scanner(高速入力)
 */
struct Scanner {
 public:
  explicit Scanner(std::FILE* fp) : fp(fp) {}

  template <typename T, typename... E>
  void read(T& t, E&... e) {
    read_single(t);
    read(e...);
  }

 private:
  static constexpr std::size_t line_size = 1 << 16;
  static constexpr std::size_t int_digits = 20;
  char line[line_size + 1] = {};
  std::FILE* fp = nullptr;
  char* st = line;
  char* ed = line;

  void read() {}

  static inline bool is_space(char c) { return c <= ' '; }

  void reread() {
    std::ptrdiff_t len = ed - st;
    std::memmove(line, st, len);
    char* tmp = line + len;
    ed = tmp + std::fread(tmp, 1, line_size - len, fp);
    *ed = 0;
    st = line;
  }

  void skip_space() {
    while (true) {
      if (st == ed) reread();
      while (*st && is_space(*st)) ++st;
      if (st != ed) return;
    }
  }

  template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
  void read_single(T& s) {
    skip_space();
    if (st + int_digits >= ed) reread();
    bool neg = false;
    if (std::is_signed<T>::value && *st == '-') {
      neg = true;
      ++st;
    }
    typename std::make_unsigned<T>::type y = *st++ - '0';
    while (*st >= '0') {
      y = 10 * y + *st++ - '0';
    }
    s = (neg ? -y : y);
  }

  template <typename T,
            std::enable_if_t<std::is_same<T, std::string>::value, int> = 0>
  void read_single(T& s) {
    s = "";
    skip_space();
    while (true) {
      char* base = st;
      while (*st && !is_space(*st)) ++st;
      s += std::string(base, st);
      if (st != ed) return;
      reread();
    }
  }

  template <typename T>
  void read_single(std::vector<T>& s) {
    for (auto& d : s) read(d);
  }
};
#pragma once
