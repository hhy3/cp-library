#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace hy {

template <typename T>
struct SparseTableOp {
  T operator()(const T &x, const T &y) {
    return std::min(x, y);
  }
};

template <typename T = int, typename IdemOp = SparseTableOp<T>> struct SparseTable {
  IdemOp op;
  int n;
  std::vector<int> log;
  std::vector<std::vector<T>> f;
  SparseTable(const std::vector<T> &v)
      : n(static_cast<int>(v.size())), log(n + 1) {
    for (int i = 2; i <= n; ++i) {
      log[i] = log[i >> 1] + 1;
    }
    f.assign(log[n] + 1, std::vector<T>(n));
    for (int i = 0; i < n; ++i) {
      f[0][i] = v[i];
    }
    for (int i = 1; i <= log[n]; ++i) {
      for (int j = 0; j + (1 << i) - 1 < n; ++j) {
        f[i][j] = op(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T query(int L, int R) {
    int j = log[R - L + 1];
    return op(f[j][L], f[j][R - (1 << j) + 1]);
  }
};

} // namespace hy
