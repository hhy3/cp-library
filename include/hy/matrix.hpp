#pragma once

#include <vector>
#include <ostream>
#include <istream>
#include <random>
#include <utility>

#include <cassert>
#include <cstdint>

namespace hy {
namespace math {


template <typename T=int64_t>
struct matrix {
  int m, n;
  std::vector<std::vector<T>> dat;
  matrix()
    : matrix(0) {}
  matrix(int m, int n)
    : m(m), n(n), dat(m, std::vector<T>(n)) {}
  explicit matrix(int m) 
    : matrix(m, m) {}
  explicit matrix(const std::vector<std::vector<T>> &vec)
    : m(vec.size()), n(vec[0].size()), dat(vec) {}
  matrix(const matrix &rhs)
    : m(rhs.m), n(rhs.n), dat(rhs.dat) {}
  matrix(matrix &&rhs) {
    swap(*this, rhs);
  }
  matrix &operator = (matrix rhs) {
    swap(*this, rhs);
    return *this;
  }
  friend void swap(matrix &lhs, matrix &rhs) noexcept {
    std::swap(lhs.m, rhs.m);
    std::swap(lhs.n, rhs.n);
    std::swap(lhs.dat, rhs.dat);
  }
  std::pair<int, int> shape() const { return std::make_pair(m, n); }
  matrix operator - () {
    matrix ans = *this;
    for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) ans.dat[i][j] *= -1;
    return ans;
  }
  matrix &operator += (const matrix &rhs) {
    assert(m == rhs.m && n == rhs.n);
    for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) dat[i][j] += rhs.data[i][j];
    return *this;
  }

  matrix operator + (const matrix &rhs) {
    assert(m == rhs.m && n == rhs.n);
    return matrix(*this) += rhs;
  }

  matrix &operator -= (const matrix &rhs) { *this += -rhs; }

  matrix operator - (const matrix &rhs) { return *this + (-rhs); }

  matrix &operator *= (const matrix &rhs) {
    assert(n == rhs.m);
    matrix tmp(m, n);
    for (int i = 0; i < m; ++i) for (int k = 0; k < n; ++k) for (int j = 0; j < rhs.n; ++j) {
      tmp[i][j] += dat[i][k] * rhs.dat[k][j];
    }
    return *this = tmp;
  }

  matrix operator * (const matrix &rhs) {
    matrix tmp = *this;
    return *this *= rhs;
  }

  matrix pow(int64_t p) {
    assert(m == n && p >= 0);
    matrix ans = eye(m), tmp = *this;
    for (; p; p >>= 1) {
      if (p & 1) ans *= tmp;
      tmp *= tmp;
    }
    return ans;
  }

  std::vector<T> &operator [] (int i) { return dat[i]; }

  static matrix eye(int n) {
    matrix tmp(n, n);
    for (int i = 0; i < n; ++i) tmp[i][i] = 1;
    return tmp;
  }

  static matrix rand(int m, int n, int64_t lo, int64_t hi) {
    matrix tmp(m, n);
    std::mt19937_64 rng;
    std::uniform_int_distribution<int64_t> dist(lo, hi);
    for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
      tmp.dat[i][j] = dist(rng);
    }
    return tmp;
  }

};


} // namespace math
} // namespace hy
