#pragma once

#include <cstdint>
#include <vector>

namespace hy {

template <typename Monoid> struct SegTreeOp {
  Monoid operator()(const Monoid &x, const Monoid &y) { return x + y; }
};

template <typename Monoid> struct MonoidId {
  Monoid operator()() { return Monoid(); }
};

// 0-indexed implmentation.
template <typename Monoid = std::int64_t, typename BinaryOp = SegTreeOp<Monoid>,
          typename ID = MonoidId<Monoid>>
struct SegTree {
  int n, size = 1;
  std::vector<Monoid> data;
  BinaryOp op;
  Monoid id = ID()();

  SegTree() {}

  explicit SegTree(int n_) : SegTree(std::vector<Monoid>(n_, id)) {}

  explicit SegTree(const std::vector<Monoid> &data_) : n(data_.size()) {
    while (size < n) {
      size <<= 1;
    }
    data.assign(size << 1, id);
    for (int i = 0; i < n; ++i) {
      data[i + size] = data_[i];
    }
    for (int i = size - 1; i >= 1; --i) {
      merge(i);
    }
  }

  void set(int i, const Monoid &x) {
    i += size;
    data[i] = x;
    for (i >>= 1; i >= 1; i >>= 1) {
      merge(i);
    }
  }

  void apply(int i, const Monoid &x) {
    i += size;
    data[i] = op(data[i], x);
    for (i >>= 1; i >= 1; i >>= 1) {
      merge(i);
    }
  }

  void get(int i) { return data[i + size]; }

  Monoid prod(int l, int r) {
    Monoid lhs = id, rhs = id;
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
