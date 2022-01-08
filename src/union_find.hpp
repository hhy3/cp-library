#pragma once

#include <vector>
#include <numeric>
#include <cassert>

/**
 * @brief 并查集 (union find)
 * 1-indexed 实现
 * 简介: https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 * 模板题: https://www.luogu.com.cn/problem/P3367
 * 
 */
class union_find {

private:

  size_t __n;
  std::vector<int> __parent, __size;

public:

  /**
   * @brief 构造函数
   * 
   * @param n
   */
  explicit 
  union_find(size_t n): __n(n), __parent(n + 1), __size(n + 1) {
    std::iota(__parent.begin(), __parent.end(), 0);
  } 

  /**
   * @brief 寻找某一元素所在集合的代表元素
   * 
   * @param u 
   * @return int 
   */
  int find(int u) {
    assert(u >= 1 && u <= __n);
    return u == __parent[u]? u : __parent[u] = find(__parent[u]);
  }

  /**
   * @brief 将u所在集合合并至v所在集合
   * 
   * @param u 
   * @param v 
   * @return true 
   * @return false 
   */
  bool merge(int u, int v) {
    assert(u >= 1 && u <= __n && v >= 1 && v <= __n);
    if (int pu = find(u), pv = find(v); pu == pv) {
      return false;
    } else {
      __size[pv] += __size[pu];
      __parent[pu] = pv;
      return true;
    } 
  }

  /**
   * @brief 判断u和v是否在一个集合之中
   * 
   * @param u 
   * @param v 
   * @return true 
   * @return false 
   */
  bool is_connected(int u, int v) {
    assert(u >= 1 && u <= __n && v >= 1 && v <= __n);
    return find(u) == find(v);
  }
  
};



