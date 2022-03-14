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

/**
 * @brief TODO
 * 
 * @tparam T 
 */
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

  std::pair<int, int> shape() const {
    return std::make_pair(m, n);
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
      for (int k = 0; k < n; ++k) {
        for (int j = 0; j < rhs.n; ++j) {
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
      for (int k = 0; k < n; ++k) {
        for (int j = 0; j < rhs.n; ++j) {
          tmp[i][j] = (tmp[i][j] + dat[i][k] * rhs.dat[k][j]) % mod;
        }
      }
    }
    return *this = tmp;
  } 

  matrix modmul(const matrix &rhs, uint64_t mod) {
    matrix tmp = *this;
    return tmp.modmul_inplace(rhs, mod);
  }

  matrix pow(int64_t p) {
    assert(m == n && p >= 0);
    assert(p >= 0);
    matrix ans = eye(m);
    matrix tmp = *this;
    for (; p; p >>= 1) {
      if (p & 1) ans *= tmp;
      tmp *= tmp;
    }
    return ans;
  }

  matrix modpow(int64_t p, uint64_t mod) {
    assert(m == n && p >= 0);
    matrix ans = eye(m);
    matrix tmp = *this;
    for (; p; p >>= 1) {
      if (p & 1) ans.modmul_inplace(tmp, mod);
      tmp.modmul_inplace(tmp, mod);
    }
    return ans;
  }

  std::vector<T> &operator [] (int i) {
    return dat[i];
  }

  static matrix eye(int n) {
    matrix tmp(n, n);
    for (int i = 0; i < n; ++i) tmp[i][i] = 1;
    return tmp;
  }

  static matrix rand(int m, int n, int64_t lo, int64_t hi) {
    matrix tmp(m, n);
    std::mt19937_64 rng;
    std::uniform_int_distribution<int64_t> dist(lo, hi);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        tmp.dat[i][j] = dist(rng);
      }
    }
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


} // namespace math
} // namespace hy