#pragma once

#include <vector>
#include <array>
#include <cmath>

/**
 * @brief 倍增求树上最近公共祖先 (Lowest common ancestor)
 *        
 *        简介: https://cp-algorithms.com/graph/lca_binary_lifting.html
 *        模板题: https://www.luogu.com.cn/problem/P3379
 * 
 *        Time Complexity: O(m * n)
 *        
 */
class LCA {

private:

  using graph = std::vector<std::vector<int>>;

  graph G;
  int n, r;

  const static int MAXM = 20;
  std::vector<std::array<int, MAXM>> up;
  std::vector<int> depth;

public:

  LCA(const graph &G, int n, int r)
      : G(G), n(n), r(r), up(n + 1), depth(n + 1) {
    init();
  }

  int get_lca(int u, int v) {
    if (depth[u] < depth[v]) {
      std::swap(u, v);
    }
    for (int j = MAXM - 1; j >= 0; --j) {
      if (depth[u] - (1 << j) >= depth[v]) {
        u = up[u][j];
      }
    }
    if (u == v) return u;
    for (int j = MAXM - 1; j >= 0; --j) {
      if (up[u][j] != up[v][j]) {
        u = up[u][j];
        v = up[v][j];
      }
    }
    return up[u][0];
  }

private:

  void init() {
    dfs(r, 0);
  }

  void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    up[u][0] = p;
    for (int i = 1; i < MAXM; ++i) {
      up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v : G[u]) if (v != p) {
      dfs(v, u);
    }
  }

};
