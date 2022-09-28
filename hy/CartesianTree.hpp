#pragma once

#include <vector>
#include <array>

namespace hy {

template <typename T>
struct CartesianTree {
  int n;
  std::vector<std::array<int, 2>> tree;
  std::vector<int> stk; // Loop invariant: stk is monotone increasing.
  CartesianTree(std::vector<T>& v, int n): n(n), tree(n, {-1, -1}) {
    for (int i = 0; i < n; ++i) {
      int pre = -1;
      while (stk.size() && v[stk.back()] >= v[i]) pre = stk.back(), stk.pop_back();
      if (stk.size()) tree[stk.back()][1] = i;
      tree[i][0] = pre;
      stk.push_back(i);
    }
  }
  std::array<int, 2>& operator [] (int i) { return tree[i]; }
};

}
