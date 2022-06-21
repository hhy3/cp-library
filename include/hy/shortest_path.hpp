#pragma once

#include <vector>
#include <set>
#include <deque>

#include <cstdint>

namespace hy {
namespace graph {

struct SP { 

  static constexpr int64_t INF = static_cast<int64_t>(1e18);

  using graph = std::vector<std::vector<std::pair<int, int64_t>>>;
  using adjMatrix = std::vector<std::vector<int64_t>>;

  static std::vector<int64_t> dijkstra(const graph &G, int src) {
    int n = G.size();
    std::vector<int64_t> dist(n, INF);
    dist[src] = 0;
    std::set<std::pair<int64_t, int>> st;
    for (int i = 0; i < n; ++i) {
      st.emplace(dist[i], i);
    }
    while (st.size()) {
      auto [d, u] = *st.begin();
      st.erase(st.begin());
      for (auto [v, w] : G[u]) {
        if (d + w < dist[v]) {
          st.erase({dist[v], v});
          dist[v] = d + w;
          st.emplace(dist[v], v);
        }
      }
    }
  }

  static void floyd(adjMatrix& adj) {
    int n = (int)adj.size();
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) 
      adj[i][j] = std::min(adj[i][j], adj[i][k] + adj[k][j]);
  }

  static std::vector<int64_t>& bfs01(const graph& G, int src) {
    int n = (int)G.size();
    std::vector<int64_t> dist(n, INF);
    dist[src] = 0;
    std::deque<int> q;
    q.push_front(src);
    while (q.size()) {
      int u = q.front(); q.pop_front();
      for (auto [v, w] : G[u]) {
        if (dist[v] + w < dist[u]) {
          dist[u] = dist[v] + w;
          if (w == 1) q.push_back(v);
          else q.push_front(v);
        }
      }
    }
  }
    
};

} // namespace shortest_path
} // namespace graph
