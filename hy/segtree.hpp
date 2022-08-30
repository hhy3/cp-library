#pragma once

#include <vector>
#include <functional>
#include <stdint.h>

namespace hy {
namespace ds {

template <typename T=int64_t>
struct SegTree {
  T id = T();
  std::function<T(T, T)> combine = [&] (const T& x, const T& y) { return x + y; };
  int n;
  std::vector<T> dat;
  SegTree() {}
  SegTree(int n): n(n), dat(4*n) {}
  template <typename Iter>
  SegTree(Iter first, Iter last): n(last-first), dat(4*n) {
    std::function<void(int, int, int)> build = [&] (int p, int l, int r) {
      if (l == r) { dat[p] = *(first + l - 1); return; }
      int mid = l + r >> 1;
      build(p<<1, l, mid), build(p<<1|1, mid+1, r);
      dat[p] = combine(dat[p<<1], dat[p<<1|1]);
    };
    build(1, 1, n);
  }

  void set(int i, int x) { return set(i, x, 1, 1, n); }

  void set(int i, int x, int p, int l, int r) {
    if (l == r) return dat[p] = x, void();
    int mid = l + r >> 1;
    if (i <= mid) set(i, x, p<<1, l, mid);
    else set(i, x, p<<1|1, mid+1, r); 
    dat[p] = combine(dat[p<<1], dat[p<<1|1]); 
  } 

  T reduce(int L, int R) { return reduce(L, R, 1, 1, n); }

  T reduce(int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) return dat[p];
    if (r < L || R < l) return id;
    int mid = l + r >> 1;
    return combine(reduce(L, R, p<<1, l, mid), reduce(L, R, p<<1|1, mid+1, r));
  }
};


template <typename T=int64_t>
struct LazySegTree {
  int n;
  struct node { T x = 0, add = 0, set = 0; };
  std::vector<node> tr;
  LazySegTree() {}
  LazySegTree(int n): n(n), tr(4*n+1) {}
  template <typename Iter>
  LazySegTree(Iter first, Iter last): n(last-first), tr(4*n+1) {
    std::function<void(int, int, int)> build = [&] (int p, int l, int r) {
      if (l == r) return tr[p].x = *(first + l - 1), void();
      int mid = l + r >> 1;
      build(p<<1, l, mid), build(p<<1|1, mid+1, r);
      pushup(p, l, r);
    };
    build(1, 1, n);
  }

  void pushup(int p, int l, int r) { tr[p].x = tr[p<<1].x + tr[p<<1|1].x; }

  void pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    if (tr[p].set) {
      tr[p<<1].x = tr[p].set * (mid - l + 1);
      tr[p<<1|1].x = tr[p].set * (r - mid);
      tr[p<<1].set = tr[p<<1|1].set = tr[p].set;
      tr[p<<1].add = tr[p<<1|1].add = tr[p].add = 0;
    }
    if (tr[p].add) {
      tr[p<<1].x += tr[p].add * (mid - l + 1);
      tr[p<<1|1].x += tr[p].add * (r - mid);
      for (auto pp : {p<<1, p<<1|1}) {
        if (tr[pp].set) tr[pp].set += tr[p].add;
        else tr[pp].add += tr[p].add;
      }
    }
    tr[p].set = tr[p].add = 0;
  }

  void set(int L, int R, T x) { return set(1, 1, n, L, R, x); }

  void set(int p, int l, int r, int L, int R, T x) {
    if (l >= L && r <= R) {
      tr[p].x = x * (r - l + 1);
      tr[p].set = x;
      tr[p].add = 0;
      return;
    }
    if (l > R || r < L) return;
    pushdown(p, l, r);
    int mid = l + r >> 1;
    set(p<<1, l, mid, L, R, x), set(p<<1|1, mid+1, r, L, R, x);
    pushup(p, l, r);
  }

  void add(int L, int R, T x) { add(1, 1, n, L, R, x); }

  void add(int p, int l, int r, int L, int R, T x) {
    if (l >= L && r <= R) {
      tr[p].x += x * (r - l + 1);
      if (tr[p].set) tr[p].set += x;
      else tr[p].add += x;
      return;
    }
    if (l > R || r < L) return;
    pushdown(p, l, r);
    int mid = l + r >> 1;
    add(p<<1, l, mid, L, R, x), add(p<<1|1, mid+1, r, L, R, x);
    pushup(p, l, r);
  }

  T sum(int L, int R) { return sum(1, 1, n, L, R); }

  T sum(int p, int l, int r, int L, int R) {
    if (l >= L && r <= R) return tr[p].x;
    if (l > R || r < L) return 0;
    pushdown(p, l, r);
    int mid = l + r >> 1;
    return sum(p<<1, l, mid, L, R) + sum(p<<1|1, mid+1, r, L, R);
  }

};

} // namespace ds
} // namespace hy
