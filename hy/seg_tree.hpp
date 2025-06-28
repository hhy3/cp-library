#pragma once

#include <limits>
#include <vector>

namespace hy {

template <typename T> struct SumMonoid {
  using data_type = T;
  static T op(T a, T b) { return a + b; }
  static T e() { return 0; }
};

template <typename T> struct MinMonoid {
  using data_type = T;
  static T op(T a, T b) { return std::min(a, b); }
  static T e() { return std::numeric_limits<T>::max(); }
};

template <typename T, typename U> struct AddAction {
  using data_type = T;
  using update_type = U;
  static T apply(T data, U update, int len) { return data + update * len; }
  static U compose(U old_update, U new_update) {
    return old_update + new_update;
  }
  static U id() { return 0; }
};

template <typename T, typename U> struct SetAction {
  using data_type = T;
  using update_type = U;
  static const U NO_OP = std::numeric_limits<U>::max();

  static T apply(T data, U update, int len) { return update; }
  static U compose(U old_update, U new_update) { return new_update; }
  static U id() { return NO_OP; }
};

template <typename Monoid, typename Action> class SegmentTree {
public:
  using T = typename Monoid::data_type;
  using U = typename Action::update_type;

private:
  int n;
  std::vector<T> tree;
  std::vector<U> lazy;

  void push_up(int node) {
    tree[node] = Monoid::op(tree[node * 2], tree[node * 2 + 1]);
  }

  void apply_lazy(int node, int l, int r, const U &val) {
    tree[node] = Action::apply(tree[node], val, r - l + 1);
    lazy[node] = Action::compose(lazy[node], val);
  }

  void push_down(int node, int l, int r) {
    if (lazy[node] != Action::id()) {
      int mid = l + (r - l) / 2;
      apply_lazy(node * 2, l, mid, lazy[node]);
      apply_lazy(node * 2 + 1, mid + 1, r, lazy[node]);
      lazy[node] = Action::id();
    }
  }

  void build(const std::vector<T> &arr, int node, int l, int r) {
    if (l == r) {
      tree[node] = arr[l];
      return;
    }
    int mid = l + (r - l) / 2;
    build(arr, node * 2, l, mid);
    build(arr, node * 2 + 1, mid + 1, r);
    push_up(node);
  }

  void update(int node, int l, int r, int ql, int qr, const U &val) {
    if (ql <= l && r <= qr) {
      apply_lazy(node, l, r, val);
      return;
    }
    push_down(node, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) {
      update(node * 2, l, mid, ql, qr, val);
    }
    if (qr > mid) {
      update(node * 2 + 1, mid + 1, r, ql, qr, val);
    }
    push_up(node);
  }

  T query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return tree[node];
    }
    push_down(node, l, r);
    int mid = l + (r - l) / 2;
    T res = Monoid::e();
    if (ql <= mid) {
      res = Monoid::op(res, query(node * 2, l, mid, ql, qr));
    }
    if (qr > mid) {
      res = Monoid::op(res, query(node * 2 + 1, mid + 1, r, ql, qr));
    }
    return res;
  }

public:
  SegmentTree(const std::vector<T> &arr) {
    n = arr.size();
    tree.resize(4 * n);
    lazy.assign(4 * n, Action::id());
    if (n > 0) {
      build(arr, 1, 0, n - 1);
    }
  }

  void update(int ql, int qr, const U &val) {
    if (n > 0 && ql <= qr) {
      update(1, 0, n - 1, ql, qr, val);
    }
  }

  T query(int ql, int qr) {
    return (n > 0 && ql <= qr) ? query(1, 0, n - 1, ql, qr) : Monoid::e();
  }
};

} // namespace hy
