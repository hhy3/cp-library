#pragma once

#include <vector>
#include <numeric>
#include <cassert>

namespace hy {
namespace ds {

/**
 * @brief 并查集 (union find)
 * 1-indexed 实现
 * 简介: https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 * 模板题: https://www.luogu.com.cn/problem/P3367
 * 
 */
class union_find {

private:

  int _n;
  std::vector<int> _parent, _size;

public:

  /**
   * @brief 构造函数
   * 
   * @param n
   */
  explicit 
  union_find(size_t n): _n(n), _parent(n + 1), _size(n + 1) {
    std::iota(_parent.begin(), _parent.end(), 0);
    std::fill(_size.begin() + 1, _size.end(), 1);
  } 

  /**
   * @brief 寻找某一元素所在集合的代表元素
   * 
   * @param u 
   * @return int 
   */
  int find(int u) {
    assert(u >= 1 && u <= _n);
    return u == _parent[u]? u : _parent[u] = find(_parent[u]);
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
    assert(u >= 1 && u <= _n && v >= 1 && v <= _n);
    if (int pu = find(u), pv = find(v); pu == pv) {
      return false;
    } else {
      _size[pv] += _size[pu];
      _parent[pu] = pv;
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
    assert(u >= 1 && u <= _n && v >= 1 && v <= _n);
    return find(u) == find(v);
  }

  /**
   * @brief u所在集合元素个数
   * 
   * @param u 
   * @return int 
   */
  int size(int u) {
    assert(u >= 1 && u <= _n);
    return _size[find(u)];
  }
  
};


} // namespace ds
} // namespace hy



