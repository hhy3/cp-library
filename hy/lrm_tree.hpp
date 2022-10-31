#pragma once

#include <cstdint>
#include <vector>

namespace hy {

template <typename T> struct LRMTreePred {
  bool operator()(const T &x, const T &y) {
    // Nearest greater: return x > y;
    // Nearest smaller: return x < y;
    return x < y;
  }
};

template <typename T = std::int32_t, typename Pred = LRMTreePred<T>>
struct LRMTree {
  Pred pred;
  int n;
  std::vector<int> L, R;
  LRMTree(const std::vector<T> &v, int nx) : n(nx), L(n, -1), R(n, n) {
    for (int i = 0; i < n; ++i) {
      int j = i - 1;
      while (j >= 0 && !pred(v[j], v[i])) {
        j = L[j];
      }
      L[i] = j;
    }
    for (int i = n - 1; i >= 0; --i) {
      int j = i + 1;
      while (j < n && !pred(v[j], v[i])) {
        j = R[j];
      }
      R[i] = j;
    }
  }
};

} // namespace hy
