#pragma once

#include <algorithm>
#include <numeric>

namespace hy {

template <typename Func, typename Comp>
double trisect(double lo, double hi, Func f, Comp comp = std::greater()) {
  for (int iter = 0; iter < 100; ++iter) {
    double m1 = (lo * 2 + hi) / 3;
    double m2 = (lo + hi * 2) / 3;
    if (comp(f(m1), f(m2))) {
      hi = m2;
    } else {
      lo = m1;
    }
  }
  return (lo + hi) / 2;
}

} // namespace hy