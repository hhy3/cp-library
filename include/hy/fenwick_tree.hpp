#pragma once

#include <vector>
#include <cstdint>
#include <cassert>

namespace hy {
namespace ds {

template <typename T=int64_t>
struct FenwickTree {
  int n;
  std::vector<T> a, b;
  FenwickTree(int n_): n(n_), a(n+1), b(n+1) {} 
  void add(int l, int r, T x) {
    add_(a, l, x), add_(a, r+1, -x), add_(b, l, x*(l-1)), add_(b, r+1, -x*r);
  }
  T sum(int i) {
    return sum_(a, i) * i - sum_(b, i); 
  }
  T sum(int l, int r) {
    return sum(r) - sum(l-1);
  }
 private:
  void add_(std::vector<T>& v, int i, T x) {
    for (; i <= n; i += i & -i) v[i] += x;
  }
  T sum_(std::vector<T>& v, int i) {
    T s = 0;
    for (; i; i -= i & -i) s += v[i];
    return s;
  }
};


} // namespace ds
} // namespace hy
