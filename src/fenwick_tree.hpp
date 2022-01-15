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

  int n;
  bool range_update;
  std::vector<T> dat, aux; 

public:
  
  /**
   * @brief 构造一个大小为n的空树状数组
   * 
   * @param n 树状数组大小
   * @param range_update 是否开启区间修改
   */
  fenwick_tree(int n, bool range_update=false): 
      n(n), range_update(range_update), dat(n + 1) {
    if (range_update) {
      aux.resize(n + 1);
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
    for (int i = 1; i <= n; ++i) {
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
    assert(index >= 1 && index <= n);
    if (range_update) {
      update(index, index, delta);
    } else {
      update(dat, index, delta);
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
    assert(L >= 1 && L <= n && R >= L && R <= n); 
    assert(range_update == true);
    update(dat, L, delta);
    update(dat, R + 1, -delta);
    update(aux, L, L * delta);
    update(aux, R + 1, -(R + 1) * delta);
  }

  /**
   * @brief 求[l, r]区间内元素和
   * 
   * @param l 
   * @param r 
   * @return T 
   */
  T query(int L, int R) const {
    assert(L >= 1 && L <= n && R >= L && R <= n);
    if (range_update) {
      return (R + 1) * query(dat, R) - query(aux, R)
             - (L * query(dat, L - 1) - query(aux, L - 1)); 
    } else {
      return query(dat, R) - query(dat, L - 1);
    }
  }

private:

  void update(std::vector<T> &v, int index, T delta) {
    for (int i = index; i <= n; i += i & -i) {
      v[i] += delta;
    }
  }

  T query(const std::vector<T> &v, int index) const {
    T ans = 0;
    for (int i = index; i > 0; i -= i & -i) {
      ans += v[i];
    }
    return ans;
  }

};