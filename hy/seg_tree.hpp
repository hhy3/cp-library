#pragma once

#include <cstdint>
#include <functional>
#include <limits>
#include <vector>

namespace hy {

// 0-indexed implmentation.
#if __cplusplus >= 201703L

template <typename S, auto op, auto e> struct SegTree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif

  int n, size = 1;
  std::vector<S> data;

  SegTree() {}

  explicit SegTree(int n_) : SegTree(std::vector<S>(n_, e())) {}

  explicit SegTree(const std::vector<S> &data_) : n(data_.size()) {
    while (size < n) {
      size <<= 1;
    }
    data.assign(size << 1, e());
    for (int i = 0; i < n; ++i) {
      data[i + size] = data_[i];
    }
    for (int i = size - 1; i >= 1; --i) {
      merge(i);
    }
  }

  void set(int i, const S &x) {
    i += size;
    data[i] = x;
    for (i >>= 1; i >= 1; i >>= 1) {
      merge(i);
    }
  }

  template <typename F> void apply(int i, F f) {
    i += size;
    data[i] = f(data[i]);
    for (i >>= 1; i >= 1; i >>= 1) {
      merge(i);
    }
  }

  S get(int i) { return data[i + size]; }

  S prod(int l, int r) {
    S lhs = e(), rhs = e();
    for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
      if (l % 2 == 1) {
        lhs = op(lhs, data[l++]);
      }
      if (r % 2 == 0) {
        rhs = op(data[r--], rhs);
      }
    }
    return op(lhs, rhs);
  }

  void merge(int i) { data[i] = op(data[i << 1], data[i << 1 | 1]); }
};

} // namespace hy
