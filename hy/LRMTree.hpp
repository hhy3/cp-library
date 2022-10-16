#pragma once

#include <vector>

namespace hy {

struct LRMTree {
  int n;
  std::vector<int> f;
  LRMTree(const std::vector<int>& v, int nx) : n(nx), f(n, -1) {
    for (int i = 0; i < n; ++i) {
      int j = i - 1;
      while (j >= 0 && v[j] >= v[i]) j = f[j];
      f[i] = j;
    }
  }
  int operator[](int idx) { return f[idx]; }
};

}  // namespace hy
