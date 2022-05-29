#pragma once

#include <istream>
#include <ostream>
#include <type_traits>
#include <cassert>

namespace hy {
namespace math {


template <uint64_t M>
struct modint {
  uint64_t _x;  
  modint(): modint(0) {}
  template <typename T>
  modint(T x) {
    if (std::is_signed<T>::value) _x = (x % T(M) + T(M)) % T(M);
    else _x = x % M;
  }

  modint(const modint& rhs): _x(rhs._x) {}

  modint& operator = (const modint& rhs) {
    _x = rhs._x;
    return *this;
  }

  operator uint64_t() { return this->_x; }

  uint64_t val() { return _x; }

  modint& operator ++ () {
    _x = (_x + 1) % M;
    return *this;
  }

  modint operator ++ (int) {
    auto ret = *this;
    ++*this;
    return ret;
  }

  modint& operator -- () {
    _x = (_x - 1 + M) % M;
    return *this;
  }

  modint operator -- (int) {
    auto ret = *this;
    --*this;
    return ret;
  }

  modint& operator += (const modint& rhs) {
    _x = (_x + rhs._x) % M;
    return *this;
  } 

  modint& operator -= (const modint& rhs) {
    _x = (_x - rhs._x + M) % M;
    return *this;
  }

  modint& operator *= (const modint& rhs) {
    _x = _x * rhs._x % M;
    return *this;
  }

  modint& operator /= (const modint& rhs) {
    return *this *= rhs.inv();
  } 

  modint inv() const {
    assert(_x > 0);
    int64_t u, v, d = extgcd(int64_t(_x), int64_t(M), u, v);
    assert(d == 1);
    return modint(u);
  }

  modint pow(int b) {
    assert(b >= 0);
    modint ret = 1, tmp = *this;
    for (; b; b >>= 1) {
      if (b & 1) ret *= tmp;
      tmp *= tmp;
    }
    return ret;
  }

  friend modint operator + (const modint& lhs, const modint &rhs) {
    return modint(lhs) += rhs;
  }
  friend modint operator - (const modint& lhs, const modint &rhs) {
    return modint(lhs) -= rhs;
  }
  friend modint operator * (const modint& lhs, const modint &rhs) {
    return modint(lhs) *= rhs;
  }
  friend modint operator / (const modint& lhs, const modint &rhs) {
    return modint(lhs) /= rhs;
  }
  friend bool operator == (const modint& lhs, const modint &rhs) {
    return lhs._x == rhs._x;
  }
  friend bool operator != (const modint& lhs, const modint &rhs) {
    return lhs._x != rhs._x;
  }
  friend std::ostream& operator << (std::ostream& os, const modint& rhs) {
    os << rhs._x;
    return os;
  }
  friend std::istream& operator >> (std::istream& is, modint& rhs) {
    is >> rhs._x;
    return is;
  }
  template <typename T>
  static T extgcd(T a, T b, T& x, T& y) {
    if (b == 0) {
      x = 1, y = 0;
      return a;
    }
    T d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
  }

};


} // namespace math
} // namespace hy
