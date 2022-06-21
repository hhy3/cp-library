#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <cstdint>

namespace hy {
namespace graph {

struct FlowEdge {
  int to, rev;
  int64_t cap;
};
using FlowGraph = std::vector<std::vector<FlowEdge>>;

struct MaxFlow {
  int n;
  FlowGraph G;
  explicit MaxFlow(int n_): n(n_), G(n) {}
  void add_edge(int u, int v, int64_t w) {
    G[u].push_back({v, (int)G[v].size(), w});
    G[v].push_back({u, (int)G[u].size()-1, 0});
  }
  int64_t flow(int s, int t) {
    std::vector<int> level(n), iter(n);
    auto bfs = [&] () -> bool {
      std::fill(level.begin(), level.end(), -1);
      level[s] = 0;
      std::queue<int> q;
      q.push(s);
      while (q.size()) {
        auto u = q.front(); q.pop();
        for (auto [to, rev, cap] : G[u]) if (level[to] == -1 && cap) {
          level[to] = level[u] + 1, q.push(to);
        }
      }
      return level[t] >= 0;
    };
    std::function<int64_t(int, int64_t)> dfs = [&] (int u, int64_t lim) {
      if (u == t || !lim) return lim;
      int64_t res = 0;
      for (int& i = iter[u]; i < (int)G[u].size(); ++i) {
        auto& [to, rev, cap] = G[u][i];
        if (int64_t d; level[to] == level[u] + 1 && (d = dfs(to, std::min(lim, cap)))) {
          cap -= d, G[to][rev].cap += d, res += d, lim -= d;
        }
      }
      return res;
    };
    int64_t f = 0;
    while (bfs()) {
      std::fill(iter.begin(), iter.end(), 0);
      f += dfs(s, INT64_MAX);
    }
    return f;
  }
  std::vector<bool> cut(int s) { // call this after flow().
    std::vector<bool> vis(n);
    vis[s] = true;
    std::queue<int> q;
    q.push(s);
    while (q.size()) {
      auto u = q.front(); q.pop();
      for (auto [to, rev, cap] : G[u]) if (!vis[to] && cap) {
        q.push(to);
        vis[to] = true;
      }
    }
    return vis;
  }
};

}
}