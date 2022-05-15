#pragma once

#include <vector>
#include <functional>
#include <stdint.h>

namespace hy {
namespace ds {

/**
 * @brief 线段树
 *        
 *        简介: 
 *            https://cp-algorithms.com/data_structures/segment_tree.html
 *            https://oi-wiki.org/ds/seg/
 *            
 *        模板题: 
 *            https://leetcode-cn.com/problems/range-sum-query-mutable/
 *            https://www.luogu.com.cn/problem/P3372 
 *            https://www.luogu.com.cn/problem/P3373
 *  
 */
template <typename T=int64_t>
struct SegTree {

  T id = T();

  std::function<T(T, T)> combine = [&] (const T& x, const T& y) {
    return x + y;
  };

  int n;
  std::vector<T> dat;

  SegTree() {}
  
  SegTree(int n): n(n), dat(4*n) {}

  template <typename Iter>
  SegTree(Iter first, Iter last): n(last-first), dat(4*n) {
    function<void(int, int, int)> build = [&] (int p, int l, int r) {
      if (l == r) {
        dat[p] = *(first + l - 1);
        return;
      }
      int mid = l + r >> 1;
      build(p<<1, l, mid);
      build(p<<1|1, mid+1, r);
      dat[p] = combine(dat[p<<1], dat[p<<1|1]);
    };
    build(1, 1, n);
  }

  void reserve(int n) {
    this->n = n;
    dat.resize(4*n);
  }

  void set(int i, int x) { 
    return set(i, x, 1, 1, n);
  }

  void set(int i, int x, int p, int l, int r) {
    if (l == r) {
      dat[p] = x;
      return;
    }
    int mid = l + r >> 1;
    if (i <= mid) {
      set(i, x, p<<1, l, mid);
    } else {
      set(i, x, p<<1|1, mid+1, r);
    }
    dat[p] = combine(dat[p<<1], dat[p<<1|1]); 
  } 

  T reduce(int L, int R) {
    return reduce(L, R, 1, 1, n);
  }

  T reduce(int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) {
      return dat[p];
    }
    if (r < L || R < l) {
      return id;
    }
    int mid = l + r >> 1;
    T lval = reduce(L, R, p<<1, l, mid);
    T rval = reduce(L, R, p<<1|1, mid+1, r);
    return combine(lval, rval); 
  }

};


template <typename T=int64_t>
struct LazySegTree {

  T id = T();

  std::function<T(T, T)> combine = [&] (const T& x, const T& y) {
    return x + y;
  };

  int n;
  std::vector<T> dat, lazy;

  LazySegTree() {}

  LazySegTree(int n): n(n), dat(4*n), lazy(4*n) {}

  template <typename Iter>
  LazySegTree(Iter first, Iter last): n(last-first), dat(4*n), lazy(4*n) {
    function<void(int, int, int)> build = [&] (int p, int l, int r) {
      if (l == r) {
        dat[p] = *(first + l - 1);
        return;
      }
      int mid = l + r >> 1;
      build(p<<1, l, mid);
      build(p<<1|1, mid+1, r);
      dat[p] = combine(dat[p<<1], dat[p<<1|1]);
    };
    build(1, 1, n);
  }

  void reserve(int n) {
    this->n = n;
    dat.resize(4*n);
  }

  void pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    dat[p<<1] += lazy[p] * (mid - l + 1);
    dat[p<<1|1] += lazy[p] * (r - mid);
    lazy[p<<1] += lazy[p];
    lazy[p<<1|1] += lazy[p];
    lazy[p] = 0;
  }

  void set(int i, T x) { 
    return set(i, x, 1, 1, n);
  }

  void set(int i, T x, int p, int l, int r) {
    if (l == r) {
      dat[p] = x;
      return;
    }
    pushdown(p, l, r);
    int mid = l + r >> 1;
    if (i <= mid) {
      set(i, x, p<<1, l, mid);
    } else {
      set(i, x, p<<1|1, mid+1, r);
    }
    dat[p] = combine(dat[p<<1], dat[p<<1|1]); 
  } 

  void add_range(int L, int R, T x) {
    add_range(L, R, x, 1, 1, n);
  }

  void add_range(int L, int R, T x, int p, int l, int r) {
    if (L <= l && r <= R) {
      dat[p] += x * (r - l + 1);
      lazy[p] += x;
      return;
    }
    if (r < L || R < l) {
      return;
    }
    pushdown(p, l, r);
    int mid = l + r >> 1;
    add_range(L, R, x, p<<1, l, mid);
    add_range(L, R, x, p<<1|1, mid+1, r);
    dat[p] = combine(dat[p<<1], dat[p<<1|1]); 
  }

  T reduce(int L, int R) {
    return reduce(L, R, 1, 1, n);
  }

  T reduce(int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) {
      return dat[p];
    }
    if (r < L || R < l) {
      return id;
    }
    pushdown(p, l, r);
    int mid = l + r >> 1;
    T lval = reduce(L, R, p<<1, l, mid);
    T rval = reduce(L, R, p<<1|1, mid+1, r);
    return combine(lval, rval); 
  }

};


} // namespace ds
} // namespace hy