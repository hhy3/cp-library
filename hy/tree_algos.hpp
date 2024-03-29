#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <queue>
#include <string>
#include <vector>

namespace hy {

struct LCA {
  using Tree = std::vector<std::vector<int>>;
  static constexpr int MAXM = 20;
  const Tree &G;
  int n, r;
  std::vector<std::array<int, MAXM>> f;
  std::vector<int> depth;
  LCA(const Tree &G, int n, int r) : G(G), n(n), r(r), f(n + 1), depth(n + 1) {
    dfs(r, 0);
  }
  int get_lca(int u, int v) {
    if (depth[u] < depth[v])
      std::swap(u, v);
    for (int j = MAXM - 1; j >= 0; --j)
      if (depth[f[u][j]] >= depth[v])
        u = f[u][j];
    if (u == v)
      return u;
    for (int j = MAXM - 1; j >= 0; --j)
      if (f[u][j] != f[v][j])
        u = f[u][j], v = f[v][j];
    return f[u][0];
  }
  void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    f[u][0] = p;
    for (int i = 1; i < MAXM; ++i)
      f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto v : G[u])
      if (v != p)
        dfs(v, u);
  }
};

struct heavy_light_decomposition {
  using Tree = std::vector<std::vector<int>>;
  int n;
  const Tree &G;
  std::vector<int> parent, depth, heavy, head, pos, dfn;
  int cur_time = 0;
  heavy_light_decomposition(const Tree &G, int s, int n) : n(n), G(G) {
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
    for (auto v : G[u])
      if (v != parent[u]) {
        parent[v] = u;
        depth[v] = depth[u] + 1;
        int c_sz = dfs(v);
        sz += c_sz;
        if (c_sz > mx_sz)
          mx_sz = c_sz, heavy[u] = v;
      }
    return sz;
  }
  void decompose(int u, int h) {
    head[u] = h;
    dfn[u] = ++cur_time;
    if (heavy[u] != -1)
      decompose(heavy[u], h);
    for (auto v : G[u])
      if (v != parent[u] && v != heavy[u])
        decompose(v, v);
  }
};

struct Prufer {
  static std::vector<int> encode(const std::vector<std::vector<int>> &G) {
    int n = G.size();
    std::vector<int> parent(n, -1), code(n - 2), deg(n);
    std::function<void(int)> dfs = [&](int u) {
      for (auto v : G[u])
        if (v != parent[u])
          parent[v] = u, dfs(v);
    };
    dfs(n - 1);
    int ptr = -1;
    for (int i = 0; i < n; ++i) {
      if ((deg[i] = (int)G[i].size()) == 1 && ptr == -1)
        ptr = i;
    }
    for (int i = 0, u = ptr; i < n - 2; ++i) {
      int v = parent[u];
      code[i] = v;
      if (--deg[v] == 1 && v <= ptr)
        u = v;
      else {
        while (deg[++ptr] != 1)
          ;
        u = ptr;
      }
    }
    return code;
  }
  static std::vector<std::vector<int>> decode(const std::vector<int> &code) {
    int n = code.size() + 2;
    std::vector<int> deg(n, 1);
    for (auto x : code)
      deg[x]++;
    int ptr = -1;
    while (deg[++ptr] != 1)
      ;
    int u = ptr;
    std::vector<std::vector<int>> G(n);
    for (auto v : code) {
      G[u].push_back(v), G[v].push_back(u);
      if (--deg[v] == 1 && v <= ptr)
        u = v;
      else {
        while (deg[++ptr] != 1)
          ;
        u = ptr;
      }
    }
    G[u].push_back(n - 1), G[n - 1].push_back(u);
    return G;
  }
};

struct Centroids {
  std::vector<int> sz, weight;
  std::vector<int> centroids;
  Centroids(const std::vector<std::vector<int>> &G, int n)
      : sz(n, 1), weight(n) {
    std::function<void(int, int)> dfs = [&](int u, int p) {
      for (auto v : G[u])
        if (v != p) {
          dfs(v, u);
          sz[u] += sz[v];
          weight[u] = std::max(weight[u], sz[v]);
        }
      weight[u] = std::max(weight[u], n - sz[u]);
      if (weight[u] <= n / 2) {
        centroids.push_back(u);
      }
    };
    dfs(0, -1);
  }
  int size() { return centroids.size(); }
  int operator[](int idx) { return centroids[idx]; }
};

struct Diameter {
  int n;
  int diameter;
  int x, y;
  std::vector<int> d0, dx, dy;
  explicit Diameter(const std::vector<std::vector<int>> &G) {
    n = (int)G.size();
    auto get = [&](int s) {
      std::vector<int> d(n, -1);
      d[s] = 0;
      std::queue<int> q;
      q.push(s);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
          if (d[v] == -1) {
            d[v] = d[u] + 1;
            q.push(v);
          }
        }
      }
      return d;
    };
    d0 = get(0);
    x = int(std::max_element(d0.begin(), d0.end()) - d0.begin());
    dx = get(x);
    y = int(std::max_element(dx.begin(), dx.end()) - dx.begin());
    dy = get(y);
    diameter = dx[y];
  }
};

struct DiameterDP {
  int n;
  int diameter = 0;
  explicit DiameterDP(const std::vector<std::vector<int>> &G) {
    n = G.size();
    std::vector<int> f1(n), f2(n);
    std::function<void(int, int)> dfs = [&](int u, int p) {
      for (auto v : G[u])
        if (v != p) {
          dfs(v, u);
          int x = f1[v] + 1;
          if (x > f1[u]) {
            f2[u] = f1[u];
            f1[u] = x;
          } else if (x > f2[u]) {
            f2[u] = x;
          }
        }
      diameter = std::max(diameter, f1[u] + f2[u]);
    };
    dfs(0, -1);
  }
};

struct AllLongestPath {
  int n;
  std::vector<int> distance;
  explicit AllLongestPath(const std::vector<std::vector<int>> &G) {
    n = G.size();
    distance.resize(n);
    int c = 0;
    std::vector<std::array<int, 2>> dist(n);
    std::function<void(int, int, int, int)> dfs = [&](int u, int p, int d,
                                                      int i) {
      dist[u][i] = d;
      if (d > dist[c][i])
        c = u;
      for (auto v : G[u])
        if (v != p) {
          dfs(v, u, d + 1, i);
        }
    };
    dfs(0, -1, 0, 0);
    dfs(c, -1, 0, 0);
    dfs(c, -1, 0, 1);
    for (int i = 0; i < n; ++i) {
      distance[i] = std::max(dist[i][0], dist[i][1]);
    }
  }
};

// Worst case: O(n^2)
std::string AHU(const std::vector<std::vector<int>> &tree, int s) {
  std::string ans;
  std::function<std::string(int, int)> dfs = [&](int u, int p) {
    std::vector<std::string> b;
    for (auto v : tree[u])
      if (v != p) {
        b.push_back(dfs(v, u));
      }
    std::sort(b.begin(), b.end());
    std::string s = "(";
    for (auto &x : b)
      s += x;
    s += ")";
    return s;
  };
  return dfs(s, -1);
}

} // namespace hy
