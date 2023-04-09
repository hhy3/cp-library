#pragma once

#include <vector>
#include <cstdint>

namespace hy {

template <typename Func> struct FunctionalGraph {
  int n, M;
  Func f;
  std::vector<std::vector<int>> jumptable;
  std::vector<std::vector<int>> RG;
  std::vector<int> cycle_into;
  std::vector<int> cycle_len;
  explicit FunctionalGraph(int n_, Func f_) : n(n_), f(f_) {}

  void build_jumptable(int M_) {
    M = M_;
    jumptable.assign(M + 1, std::vector<int>(n));
    for (int j = 0; j < n; ++j) {
      jumptable[0][j] = f(j);
    }
    for (int i = 1; i <= M; ++i) {
      for (int j = 0; j < n; ++j) {
        jumptable[i][j] = jumptable[i - 1][jumptable[i - 1][j]];
      }
    }
  }
  int jump(int u, int64_t x) {
    for (int i = 0; i <= M; ++i) {
      if (x >> i & 1) {
        u = jumptable[i][u];
      }
    }
    return u;
  }

  void build_reverse() {
    RG.assign(n, {});
    for (int i = 0; i < n; ++i) {
      RG[f(i)].push_back(i);
    }
  }
  void build_cycle() {
    cycle_into.assign(n, -1);
    cycle_len.assign(n, -1);
    build_reverse();
    auto calc = [&](int u) {
      int x = f(u), y = f(f(u));
      while (x != y) {
        x = f(x);
        y = f(f(y));
      }
      y = u;
      while (x != y) {
        x = f(x);
        y = f(y);
      }
      cycle_into[x] = x;
      int len = 1;
      for (x = f(x); x != y; x = f(x)) {
        cycle_into[x] = x;
        len++;
      }
      auto dfs = [&](auto self, int uu, int s) -> void {
        for (auto vv : RG[uu]) {
          if (cycle_into[vv] == -1) {
            cycle_into[vv] = s;
            self(self, vv, s);
          }
        }
      };
      for (int i = 0; i < len; ++i) {
        cycle_len[x] = len;
        dfs(dfs, x, x);
        x = f(x);
      }
    };
    for (int i = 0; i < n; ++i) {
      if (cycle_into[i] == -1) {
        calc(i);
      }
    }
  }
};

}