#pragma once

#include <charconv>
#include <cstddef>
#include <cstdio>
#include <string>
#include <type_traits>
#include <vector>

/**
 * @brief Printer(高速出力)
 */
struct Printer {
 public:
  explicit Printer(FILE* fp) : fp(fp) {}

  ~Printer() { flush(); }

  template <bool f = false, typename T, typename... E>
  void write(const T& t, const E&... e) {
    if (f) write_single(' ');
    write_single(t);
    write<true>(e...);
  }

  template <typename... T>
  void writeln(const T&... t) {
    write(t...);
    write_single('\n');
  }

  void flush() {
    fwrite(line, 1, st - line, fp);
    st = line;
  }

 private:
  FILE* fp = nullptr;
  static constexpr std::size_t line_size = 1 << 16;
  static constexpr std::size_t int_digits = 20;
  char line[line_size + 1] = {};
  char* st = line;

  template <bool f = false>
  void write() {}

  void write_single(const char& t) {
    if (st + 1 >= line + line_size) flush();
    *st++ = t;
  }

  template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
  void write_single(T s) {
    if (st + int_digits >= line + line_size) flush();
    st += std::to_chars(st, st + int_digits, s).ptr - st;
  }

  void write_single(const std::string& s) {
    for (auto& c : s) write_single(c);
  }

  void write_single(const char* s) {
    while (*s != 0) write_single(*s++);
  }

  template <typename T>
  void write_single(const std::vector<T>& s) {
    for (std::size_t i = 0; i < s.size(); i++) {
      if (i) write_single(' ');
      write_single(s[i]);
    }
  }
};
