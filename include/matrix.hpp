#pragma once

#include <vector>
#include <ostream>
#include <istream>
#include <cassert>
#include <cstdint>
#include <iostream>

/**
 * @brief TODO
 * 
 * @tparam T 
 */
template <typename T=int64_t>
struct matrix {
  
  int m, n;
  std::vector<std::vector<T>> dat;

  matrix(int m, int n)
    : m(m), n(n), dat(m, std::vector<T>(n)) {}

  matrix(const std::vector<std::vector<T>> &vec)
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

  matrix operator - () {
    matrix ans = *this;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        ans.dat[i][j] *= -1;
      }
    }
    return ans;
  }

  matrix &operator += (const matrix &rhs) {
    assert(m == rhs.m);
    assert(n == rhs.n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        dat[i][j] += rhs.data[i][j];
      }
    }
    return *this;
  }

  matrix operator + (const matrix &rhs) {
    assert(m == rhs.m);
    assert(n == rhs.n);
    matrix tmp = *this;
    return tmp += rhs;
  }

  matrix &operator -= (const matrix &rhs) {
    *this += -rhs;
  }

  matrix operator - (const matrix &rhs) {
    return *this + (-rhs);
  }

  matrix &operator *= (const matrix &rhs) {
    assert(n == rhs.m);
    matrix tmp(m, n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < rhs.n; ++j) {
        for (int k = 0; k < n; ++k) {
          tmp[i][j] += dat[i][k] * rhs.dat[k][j];
        }
      }
    }
    return *this = tmp;
  }

  matrix operator * (const matrix &rhs) {
    matrix tmp = *this;
    return this *= rhs;
  }

  matrix& modmul_inplace(const matrix &rhs, uint64_t mod) {
    assert(n == rhs.m);
    matrix tmp(m, n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < rhs.n; ++j) {
        for (int k = 0; k < n; ++k) {
          tmp[i][j] = (tmp[i][j] + dat[i][k] * rhs.dat[k][j]) % mod;
        }
      }
    }
    std::cout << tmp << "\n";
    return *this = tmp;
  } 

  matrix modmul(const matrix &rhs, uint64_t mod) {
    matrix tmp = *this;
    return tmp.modmul_inplace(rhs, mod);
  }

  std::vector<T> &operator [] (int i) {
    return dat[i];
  }

  static matrix eye(int n) {
    matrix tmp(n, n);
    for (int i = 0; i < n; ++i) tmp[i][i] = 1;
    return tmp;
  }

  friend std::ostream &operator << (std::ostream &os, matrix rhs) {
    os << "matrix:\n";
    for (int i = 0; i < rhs.m; ++i) {
      os << "[ ";
      for (int j = 0; j < rhs.n; ++j) {
        os << rhs[i][j] << " ";
      }
      os << "]\n";
    }
    return os;
  } 

  friend std::istream &operator >> (std::istream &is, matrix rhs) {
    is >> rhs.m >> rhs.n;
    rhs = matrix(rhs.m, rhs.n);
    for (int i = 0; i < rhs.m; ++i) {
      for (int j = 0; j < rhs.n; ++j) {
        is >> rhs[i][j];
      }
    }
    return is;
  }

};