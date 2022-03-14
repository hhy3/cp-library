#pragma once

#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <type_traits>

#include <cassert>

namespace hy {
namespace math {

/**
 * @brief TODO 
 * 
 */
template <int base=10>
struct bigint {

  std::vector<int> dat;
  
  explicit bigint() = default;

  template <typename T, 
    typename std::enable_if<std::is_integral_v<T>, T>::type* = nullptr>
  bigint(T x) {
    for (; x; x /= 10) {
      dat.push_back(x % 10);
    }
  }

  explicit bigint(const std::string &x) {
    for (int i = (int)x.size()-1; i >= 0; --i) {
      assert(x[i] >= '0' && x[i] <= '9');
      dat.push_back(x[i]-'0');
    }
    while (dat.size() && dat.back() == 0) {
      dat.pop_back();
    }
  }

  template <typename T>
  explicit bigint(const std::vector<T> &x) {
    for (int i = 0; i < (int)x.size(); ++i) {
      assert(x[i] >= 0 && x[i] <= 9);
      dat.push_back(x[i]);
    } 
    while (dat.size() && dat.back() == 0) {
      dat.pop_back();
    }
  }

  bigint(const bigint &rhs)
    : dat(rhs.dat) {}

  bigint(bigint &&rhs) 
    : dat(move(rhs.dat)) {}

  bigint &operator = (bigint rhs) {
    swap(this->dat, rhs.dat);
    return *this;
  }

  int size() const {
    return dat.size();
  }

  int operator [] (int idx) const {
    return dat[idx];
  }

  int &operator [] (int idx) {
    return dat[idx];
  }

  friend std::istream &operator >> (std::istream &is, bigint &rhs) {
    rhs.dat.clear();
    std::string x; is >> x;
    if (x == "0") {
      return is;
    }
    for (int i = x.size()-1; i >= 0; --i) {
      rhs.dat.push_back(x[i]-'0');
    }
    return is;
  }

  friend std::ostream &operator << (std::ostream &os, const bigint &rhs) {
    if (rhs.dat.empty()) {
      os << "0";
      return os;
    }

    for (int i = rhs.dat.size()-1; i >= 0; --i) {
      os << rhs.dat[i];
    }
    return os;
  }

  friend std::string to_string(const bigint& rhs) {
    if (rhs == 0) {
      return "0";
    }
    std::string s;
    for (int i = (int)rhs.size()-1; i >= 0; --i) {
      s.push_back(rhs[i]+'0');
    }
    return s;
  } 

  bigint &operator += (const bigint &rhs) {
    for (int i = 0, r = 0; i < (int)dat.size() || i < (int)rhs.dat.size() || r; ++i) {
      if (i == (int)dat.size()) {
        dat.push_back(0);
      }
      r += dat[i];
      if (i < (int)rhs.dat.size()) {
        r += rhs.dat[i];
      }
      dat[i] = r % base;
      r /= base;
    }
    while (dat.size() && dat.back() == 0) {
      dat.pop_back();
    }
    return *this;
  }

  bigint operator + (const bigint &rhs) {
    return bigint(*this) += rhs;
  }

  bigint &operator -= (const bigint &rhs) {
    assert(*this >= rhs);
    for (int i = 0, r = 0; i < (int)dat.size(); ++i) {
      if (i < rhs.size()) dat[i] -= rhs[i];
      dat[i] -= r;
      if (dat[i] < 0) {
        dat[i] += base;
        r = 1;
      } else {
        r = 0;
      }
    }
    while (dat.size() && dat.back() == 0) {
      dat.pop_back();
    }
    return *this;
  }

  bigint operator - (const bigint &rhs) {
    return bigint(*this) -= rhs;
  }

  bigint operator * (const bigint &rhs) {
    int m = size(), n = rhs.size();
    std::vector<int> tmp(m + n);
    for (int i = 0; i < m + n - 1; ++i) {
      for (int j = 0; j <= i; ++j) {
        if (j < m && i - j < n) {
          tmp[i] += dat[j] * rhs[i-j];
        }
      }
      if (tmp[i] >= 10) {
        tmp[i+1] += tmp[i] / base;
        tmp[i] %= base;
      }
    }
    while (tmp.size() && tmp.back() == 0) {
      tmp.pop_back();
    }
    return bigint(tmp);
  }

  friend bool operator == (const bigint &lhs, const bigint &rhs) {
    if (lhs.size() != rhs.size()) {
      return false;
    }
    for (int i = 0; i < lhs.size(); ++i) {
      if (lhs[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator != (const bigint &lhs, const bigint &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator < (const bigint &lhs, const bigint &rhs) {
    if (lhs.size() < rhs.size()) {
      return true;
    }
    if (lhs.size() > rhs.size()) {
      return false;
    }
    for (int i = lhs.size()-1; i >= 0; --i) {
      if (lhs[i] < rhs[i]) return true;
      if (lhs[i] > rhs[i]) return false;
    }
    return false;
  }

  friend bool operator <= (const bigint &lhs, const bigint &rhs) {
    return lhs < rhs || lhs == rhs;
  }

  friend bool operator > (const bigint &lhs, const bigint &rhs) {
    return !(lhs <= rhs);
  }

  friend bool operator >= (const bigint &lhs, const bigint &rhs) {
    return !(lhs < rhs);
  }

};

} // namespace math
} // namespace hy