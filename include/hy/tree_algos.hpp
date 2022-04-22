#pragma once

#include <vector>
#include <array>
#include <cmath>

namespace hy {
namespace tree {


/**
 * @brief 倍增求树上最近公共祖先 (Lowest common ancestor)
 *        
 *        简介: 
 *            https://cp-algorithms.com/graph/lca_binary_lifting.html
 *        
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P3379
 *        
 *        练习题:
 *            TODO
 * 
 */
struct LCA {

  using graph = std::vector<std::vector<int>>;

  const static int MAXM = 20;

  graph G;
  int n, r;
  std::vector<std::array<int, MAXM>> up;
  std::vector<int> depth;

  LCA(const graph &G, int n, int r)
      : G(G), n(n), r(r), up(n + 1), depth(n + 1) {
    dfs(r, 0);
  }

  // Time Complexity: O(logn)
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

  // Time Complexity: O(nlogn)
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


/**
 * @brief 轻重链剖分 / 树链剖分
 *  
 *        简介:
 *            https://en.wikipedia.org/wiki/Heavy_path_decomposition
 *            https://cp-algorithms.com/graph/hld.html
 *            https://oi-wiki.org/graph/hld/
 * 
 *        模板题:
 *            https://www.luogu.com.cn/problem/P3379
 *            https://www.luogu.com.cn/problem/P3384
 * 
 *        练习题:
 *            TODO
 * 
 */
struct heavy_light_decomposition {
  
  using tree_t = std::vector<std::vector<int>>;
  
  int n;
  tree_t& G;
  std::vector<int> parent, depth, heavy, head, pos, dfn;
  int cur_time = 0;

  heavy_light_decomposition(tree_t& G, int s, int n): n(n), G(G) {
    parent.resize(n + 1);
    depth.resize(n + 1);
    heavy.resize(n + 1, -1);
    head.resize(n + 1);
    pos.resize(n + 1);  
    dfn.resize(n + 1);
    dfs(s);
    decompose(s, s);
  }

  int dfs(int u) {
    int sz = 1, mx_sz = 0;
    for (auto v : G[u]) if (v != parent[u]) {
      parent[v] = u;
      depth[v] = depth[u] + 1;
      int c_sz = dfs(v);
      sz += c_sz;
      if (c_sz > mx_sz) {
        mx_sz = c_sz;
        heavy[u] = v;
      }
    }
    return sz;
  }

  void decompose(int u, int h) {
    head[u] = h;
    dfn[u] = ++cur_time;
    if (heavy[u] != -1) {
      decompose(heavy[u], h);
    } 
    for (auto v : G[u]) if (v != parent[u] && v != heavy[u]) {
      decompose(v, v);
    }
  }

};

}
}