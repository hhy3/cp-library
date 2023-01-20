#pragma once

#include <functional>
#include <vector>
#include <queue>

namespace hy {

inline bool is_biparitite(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  std::vector<int> color(n, -1);
  std::function<bool(int, int)> dfs = [&](int u, int c) {
    color[u] = c;
    for (auto v : graph[u]) {
      if (color[v] == -1) {
        if (!dfs(v, c ^ 1)) {
          return false;
        }
      } else if (color[v] == c) {
        return false;
      }
    }
    return true;
  };
  for (int i = 0; i < n; ++i) {
    if (color[i] == -1) {
      if (!dfs(i, 0)) {
        return false;
      }
    }
  }
  return true;
}

struct SCC {
  using Graph = std::vector<std::vector<int>>;
  int n, scc_num = 0;
  const Graph& G;
  Graph S;
  std::vector<int> id, topo;
  std::vector<std::vector<int>> components;
  explicit SCC(const Graph& graph, bool build_condens = true)
      : n((int)graph.size()), G(graph), id(n, -1) {
    std::vector<bool> vis(n);
    std::vector<int> post;
    std::function<void(int)> dfs1 = [&](int u) {
      vis[u] = true;
      for (auto v : G[u]) {
        if (!vis[v]) dfs1(v);
      }
      post.push_back(u);
    };
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) dfs1(i);
    }
    Graph rG(n);
    for (int i = 0; i < n; ++i) {
      for (auto v : G[i]) rG[v].push_back(i);
    }
    std::function<void(int, int)> dfs2 = [&](int u, int idx) {
      id[u] = idx;
      components[idx].push_back(u);
      for (auto v : rG[u]) {
        if (id[v] == -1) dfs2(v, idx);
      }
    };
    for (int i = n - 1; i >= 0; --i)
      if (id[post[i]] == -1) {
        components.push_back({});
        dfs2(post[i], scc_num);
        scc_num++;
      }
    if (build_condens) {
      S.resize(scc_num);
      std::vector<int> deg(scc_num);
      for (int i = 0; i < n; ++i) {
        for (auto v : G[i]) {
          if (int x = id[i], y = id[v]; x != y) {
            S[x].push_back(y);
            deg[y]++;
          }
        }
      }
      std::queue<int> q;
      topo.reserve(scc_num);
      for (int i = 0; i < scc_num; ++i) {
        if (!deg[i]) q.push(i);
      }
      while (q.size()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (auto v : S[u]) {
          if (--deg[v] == 0) q.push(v);
        }
      }
    }
  }
};

struct GraphBridges {
  int n;
  std::vector<int> tin, low;
  std::vector<std::pair<int, int>> bridges;
  explicit GraphBridges(const std::vector<std::vector<int>>& G) {
    n = G.size();
    tin.assign(n, 0);
    low.assign(n, 0);
    int timer = 0;
    std::function<void(int, int)> dfs = [&] (int u, int p) {
      tin[u] = low[u] = ++timer;
      for (auto v : G[u]) if (v != p) {
        if (tin[v]) {
          low[u] = std::min(low[u], tin[v]);
        } else {
          dfs(v, u);
          low[u] = std::min(low[u], low[v]);
          if (tin[u] < low[v]) {
            bridges.emplace_back(std::min(u, v), std::max(u, v));
          }
        }
      }
    };
    for (int i = 0; i < n; ++i) {
      if (!tin[i]) dfs(i, -1);
    }
  }
};

struct ArticulationPoints {
  int n;
  std::vector<int> tin, low;
  std::vector<bool> is_articulation;
  explicit ArticulationPoints(const std::vector<std::vector<int>>& G) {
    n = G.size();
    tin.assign(n, -1);
    low.assign(n, -1);
    is_articulation.assign(n, false);
    std::vector<bool> vis(n);
    int timer = 0;
    std::function<void(int, int)> dfs = [&] (int u, int p) {
      vis[u] = true;
      tin[u] = low[u] = ++timer;
      int cnt = 0;
      for (auto v : G[u]) if (v != p) {
        if (vis[v]) {
          low[u] = std::min(low[u], tin[v]);
        } else {
          dfs(v, u);
          low[u] = std::min(low[u], low[v]);
          if (low[v] >= tin[u] && p != -1) {
            is_articulation[u] = true;
          }
          cnt++;
        }
      }
      if (p == -1 && cnt > 1) {
        is_articulation[u] = true;
      }
    };
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) dfs(i, -1);
    }
  }
};

} // namespace hy