#pragma once

#include <vector>
#include <functional>


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
template <typename T=int64_t, T id=T()>
struct segtree {

  struct node {
    T val = id;
    int l, r;
  };

  int n;
  std::vector<node> nodes;
  std::function<T(T, T)> combine;

  segtree(int n, std::function<T(T, T)> combine=[](T x, T y) { return x + y; })
    : n(n), nodes(4*n), combine(combine) {
    build(1, 1, n);
  }

  void build(int u, int L, int R) {
    nodes[u].l = L;
    nodes[u].r = R;
    if (L == R) {
      return;
    }
    int mid = (L + R) >> 1;
    build(2*u, L, mid);
    build(2*u+1, mid+1, R);
    nodes[u].val = combine(nodes[2*u].val, nodes[2*u+1].val);
  }

  T reduce(int L, int R) {
    return reduce(1, L, R);
  }

  T reduce(int u, int L, int R) {
    if (nodes[u].l >= L && nodes[u].r <= R) {
      return nodes[u].val;
    }
    if (nodes[u].l > R || nodes[u].r < L) {
      return id;
    }
    return combine(reduce(2*u, L, R), reduce(2*u+1, L, R));
  }

  void update(int idx, const T& val) {
    update(1, idx, val);
  }

  void update(int u, int idx, const T& val) {
    if (nodes[u].l == nodes[u].r) {
      nodes[u].val = val;
      return;
    }
    int mid = (nodes[u].l + nodes[u].r) >> 1;
    if (idx <= mid) {
      update(2*u, idx, val);
    } else {
      update(2*u+1, idx, val);
    }
    nodes[u].val = combine(nodes[2*u].val, nodes[2*u+1].val);
  }

};