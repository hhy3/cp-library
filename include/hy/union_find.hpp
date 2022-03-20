#pragma once

#include <vector>
#include <numeric>
#include <cassert>

namespace hy {
namespace ds {

/**
 * @brief 并查集 (union find) 1-indexed 实现
 *     
 *        简介: 
 *            https://cp-algorithms.com/data_structures/disjoint_set_union.html
 * 
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P3367
 *        
 *        练习题:
 *            https://www.luogu.com.cn/problem/P3958
 *            https://www.luogu.com.cn/problem/P1455
 * 
 */
struct union_find {

  struct node {
    int p;
    int sz;
  };

  int n, num_component;
  std::vector<node> nodes;

  explicit 
  union_find(size_t n): n(n), num_component(n), nodes(n) {
    for (int i = 0; i < (int)n; ++i) {
      nodes[i].p = i;
      nodes[i].sz = 1;
    }
  } 

  node& operator [] (int i) {
    return nodes[i];
  }

  int find(int u) {
    assert(u >= 0 && u < n);
    return nodes[u].p == u? u : nodes[u].p = find(nodes[u].p);
  }

  bool merge(int u, int v) {
    assert(u >= 0 && u < n && v >= 0 && v < n);
    int pu = find(u), pv = find(v);
    if (pu == pv) {
      return false;
    }
    if (nodes[pu].sz > nodes[pv].sz) {
      std::swap(pu, pv);
    }
    nodes[pu].p = pv;
    nodes[pv].sz += nodes[pu].sz;
    num_component--;
    return true;
  }

  bool is_connected(int u, int v) {
    assert(u >= 0 && u < n && v >= 0 && v < n);
    return find(u) == find(v);
  }

  int size(int u) {
    assert(u >= 0 && u < n);
    return nodes[find(u)].sz;
  }

  std::vector<int> leaders() {
    std::vector<int> ans;
    for (int i = 0; i < n; ++i) {
      if (find(i) == i) {
        ans.push_back(i);
      }
    }
    return ans;
  }
  
};


} // namespace ds
} // namespace hy



