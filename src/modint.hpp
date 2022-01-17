#pragma once

#include <istream>
#include <ostream>

/**
 * @brief 模M剩余类集合
 * 
 * @tparam M 
 */
template <int M>
class modint {
  
private:

  uint64_t _x;  

public:

  modint(uint64_t x=0): _x(((x % M) + M) % M) {}

  modint(const modint& rhs): _x(rhs._x) {}

  modint& operator = (const modint& rhs) {
    _x = rhs._x;
    return *this;
  }

  uint64_t val() {
    return _x;
  }

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
    _x = _x * rhs.inv();
    return *this;
  } 

  modint inv() {
    assert(_x > 0);
    return fastpow(M - 2);
  }

  modint fastpow(int b) {
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

};