#pragma once

#include <vector>
#include <cassert>

namespace hy {
namespace ds {

/**
 * @brief 树状数组 (fenwick tree / binary indexed tree)
 *        1-indexed 实现
 * 
 *        简介: 
 *            https://en.wikipedia.org/wiki/Fenwick_tree
 *    
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P3374
 *            https://www.luogu.com.cn/problem/P3368
 * 
 *        练习题:
 *            TODO
 * 
 * @tparam T 
 */
template <typename T>
struct fenwick_tree {

private:

  int n;
  bool range_update;
  std::vector<T> dat, aux; 

public:
  
  fenwick_tree(int n, bool range_update=false): 
      n(n), range_update(range_update), dat(n + 1) {
    if (range_update) {
      aux.resize(n + 1);
    }
  }

  template <typename U>
  fenwick_tree(const std::vector<U> v, bool range_update=false):
      fenwick_tree(int(v.size()), range_update) {
    for (int i = 1; i <= n; ++i) {
      update(i, v[i - 1]);
    }
  }

  void update(int index, T delta) {
    assert(index >= 1 && index <= n);
    if (range_update) {
      update(index, index, delta);
    } else {
      update(dat, index, delta);
    }
  }

  void update(int L, int R, T delta) {
    assert(L >= 1 && L <= n && R >= L && R <= n); 
    assert(range_update == true);
    update(dat, L, delta);
    update(dat, R + 1, -delta);
    update(aux, L, L * delta);
    update(aux, R + 1, -(R + 1) * delta);
  }

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


} // namespace ds
} // namespace hy