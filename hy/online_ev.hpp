#pragma once

#include <cstdint>

namespace hy {

template <typename T = double> struct OnlineEV {
  T s1 = 0, s2 = 0, n = 0;

  void insert(T x) { n++, s1 += x, s2 += x * x; }

  void erase(T x) { n--, s1 -= x, s2 -= x * x; }

  double E() {
    if (n == 0)
      return -1;
    return static_cast<double>(s1) / n;
  }

  double V() {
    if (n == 0)
      return -1;
    return static_cast<double>(s2) / n - static_cast<double>(s1 * s1) / n / n;
  }
};

} // namespace hy