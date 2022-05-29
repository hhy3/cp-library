#pragma once

#include <vector>
#include <functional>

template <typename T=int>
struct sparse_table {
  using idem_op = std::function<T(T, T)>;
  int n;
  std::vector<int> log; 
  std::vector<std::vector<T>> f;
  idem_op op;

  sparse_table(const std::vector<T>& v, idem_op op=[](T x, T y) { return min(x, y); })
    : n((int)v.size()), log(n+1), op(op) {
    for (int i = 2; i <= n; ++i) log[i] = log[i>>1] + 1;
    f.assign(log[n]+1, std::vector<T>(n));
    for (int i = 0; i < n; ++i) f[0][i] = v[i];
    for (int i = 1; i <= log[n]; ++i) {
      for (int j = 0; j + (1 << i) - 1 < n; ++j) {
        f[i][j] = op(f[i-1][j], f[i-1][j+(1<<(i-1))]);
      }
    }
  }

  T query(int L, int R) {
    int j = log[R-L+1];
    return op(f[j][L], f[j][R-(1<<j)+1]);
  }

};
