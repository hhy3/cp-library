#pragma once

#include <vector>

/**
 * @brief 树状数组 (fenwick tree / binary indexed tree)
 * 1-indexed 实现
 * 简介: https://en.wikipedia.org/wiki/Fenwick_tree
 * 模板题: https://www.luogu.com.cn/problem/P3374
 *        https://www.luogu.com.cn/problem/P3368
 * 
 * @tparam T 
 */
template <typename T>
class fenwick_tree {

private:

  int __n;
  bool __range_update;
  std::vector<T> __dat, __aux; 

public:
  
  /**
   * @brief 构造一个大小为n的空树状数组
   * 
   * @param n 树状数组大小
   * @param range_update 是否开启区间修改
   */
  fenwick_tree(int n, bool range_update=false): 
      __n(n), __range_update(range_update), __dat(n + 1) {
    if (__range_update) {
      __aux.resize(n + 1);
    }
  }

  /**
   * @brief 使用数组v构造树状数组
   * 
   * @tparam U 
   * @param v 
   * @param range_update 
   */
  template <typename U>
  fenwick_tree(const std::vector<U> v, bool range_update=false):
      fenwick_tree(int(v.size()), range_update) {
    for (int i = 1; i <= __n; ++i) {
      update(i, v[i - 1]);
    }
  }

  /**
   * @brief 将位置为index的元素增加delta
   * 
   * @param index 
   * @param delta 
   */
  void update(int index, T delta) {
    assert(index >= 1 && index <= __n);
    if (__range_update) {
      update(index, index, delta);
    } else {
      __update(__dat, index, delta);
    }
  }

  /**
   * @brief 将在区间[l, r]的内的所有元素增加delta
   * 
   * @param L 
   * @param R 
   * @param delta 
   */
  void update(int L, int R, T delta) {
    assert(L >= 1 && L <= __n && R >= L && R <= __n); 
    assert(__range_update == true);
    __update(__dat, L, delta);
    __update(__dat, R + 1, -delta);
    __update(__aux, L, L * delta);
    __update(__aux, R + 1, -(R + 1) * delta);
  }

  /**
   * @brief 求[l, r]区间内元素和
   * 
   * @param l 
   * @param r 
   * @return T 
   */
  T query(int L, int R) const {
    assert(L >= 1 && L <= __n && R >= L && R <= __n);
    if (__range_update) {
      return (R + 1) * __query(__dat, R) - __query(__aux, R)
             - (L * __query(__dat, L - 1) - __query(__aux, L - 1)); 
    } else {
      return __query(__dat, R) - __query(__dat, L - 1);
    }
  }

private:

  void __update(std::vector<T> &v, int index, T delta) {
    for (int i = index; i <= __n; i += i & -i) {
      v[i] += delta;
    }
  }

  T __query(const std::vector<T> &v, int index) const {
    T ans = 0;
    for (int i = index; i > 0; i -= i & -i) {
      ans += v[i];
    }
    return ans;
  }

};