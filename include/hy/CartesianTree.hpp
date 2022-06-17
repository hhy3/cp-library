#pragma once

#include <vector>

namespace hy {
namespace ds {

struct CartesianTree {
  int n;
  std::vector<int> L, R;
  std::vector<int> stk; // Loop invariant: stk is monotone increasing.
  CartesianTree(std::vector<int>& v, int n_): n(n_), L(n_, -1), R(n_, -1) {
    for (int i = 0; i < n; ++i) {
      int pre = -1;
      while (stk.size() && v[stk.back()] >= v[i]) pre = stk.back(), stk.pop_back();
      if (stk.size()) R[stk.back()] = i;
      L[i] = pre;
      stk.push_back(i);
    }
  }
};

}
}
