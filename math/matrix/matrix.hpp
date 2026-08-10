#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

template <class T>
struct Matrix {
  std::vector<std::vector<T> > A;

  Matrix() {}

  Matrix(const std::vector<std::vector<T> >& A) : A(A) {}

  Matrix(std::size_t n, std::size_t m) : A(n, std::vector<T>(m, 0)) {}

  Matrix(std::size_t n) : A(n, std::vector<T>(n, 0)) {};

  std::size_t size() const {
    if (A.empty()) return 0;
    assert(A.size() == A[0].size());
    return A.size();
  }

  std::size_t height() const { return (A.size()); }

  std::size_t width() const { return (A[0].size()); }

  inline const std::vector<T>& operator[](int k) const { return (A.at(k)); }

  inline std::vector<T>& operator[](int k) { return (A.at(k)); }

  static Matrix I(std::size_t n) {
    Matrix mat(n);
    for (int i = 0; i < n; i++) mat[i][i] = 1;
    return (mat);
  }

  Matrix& operator+=(const Matrix& B) {
    std::size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
    return (*this);
  }

  Matrix& operator-=(const Matrix& B) {
    std::size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
    return (*this);
  }

  Matrix& operator*=(const Matrix& B) {
    std::size_t n = height(), m = B.width(), p = width();
    assert(p == B.height());
    std::vector<std::vector<T> > C(n, std::vector<T>(m, 0));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        for (int k = 0; k < p; k++)
          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
    A.swap(C);
    return (*this);
  }

  Matrix& operator^=(long long k) {
    Matrix B = Matrix::I(height());
    while (k > 0) {
      if (k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix& B) const { return (Matrix(*this) += B); }

  Matrix operator-(const Matrix& B) const { return (Matrix(*this) -= B); }

  Matrix operator*(const Matrix& B) const { return (Matrix(*this) *= B); }

  Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }

  friend std::ostream& operator<<(std::ostream& os, Matrix& p) {
    std::size_t n = p.height(), m = p.width();
    for (int i = 0; i < n; i++) {
      os << "[";
      for (int j = 0; j < m; j++) {
        os << p[i][j] << (j + 1 == m ? "]\n" : ",");
      }
    }
    return (os);
  }

  T determinant() {
    Matrix B(*this);
    assert(width() == height());
    T ret = 1;
    for (int i = 0; i < width(); i++) {
      int idx = -1;
      for (int j = i; j < width(); j++) {
        if (B[j][i] != 0) idx = j;
      }
      if (idx == -1) return (0);
      if (i != idx) {
        ret *= -1;
        std::swap(B[i], B[idx]);
      }
      ret *= B[i][i];
      T vv = B[i][i];
      for (int j = 0; j < width(); j++) {
        B[i][j] /= vv;
      }
      for (int j = i + 1; j < width(); j++) {
        T a = B[j][i];
        for (int k = 0; k < width(); k++) {
          B[j][k] -= B[i][k] * a;
        }
      }
    }
    return (ret);
  }
};
