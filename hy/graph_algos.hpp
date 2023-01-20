#pragma once

#include <functional>
#include <vector>

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

struct GraphBridges {
  int n;
  std::vector<int> tin, low;
  std::vector<std::pair<int, int>> bridges;
  explicit GraphBridges(const std::vector<std::vector<int>>& G) {
    n = G.size();
    tin.assign(n, -1);
    low.assign(n, -1);
    std::vector<bool> vis(n);
    int timer = 0;
    std::function<void(int, int)> dfs = [&] (int u, int p) {
      vis[u] = true;
      tin[u] = low[u] = ++timer;
      for (auto v : G[u]) if (v != p) {
        if (vis[v]) {
          low[u] = std::min(low[u], tin[v]);
        } else {
          dfs(v, u);
          low[u] = std::min(low[u], low[v]);
          if (low[v] >= tin[u]) {
            bridges.emplace_back(u, v);
          }
        }
      }
    };
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) dfs(i, -1);
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