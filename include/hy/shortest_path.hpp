#pragma once

#include <vector>
#include <set>

#include <cstdint>

namespace hy {
namespace graph {

struct SP { 

  static constexpr int64_t INF = static_cast<int64_t>(1e18);

  using graph = std::vector<std::vector<std::pair<int, int64_t>>>;
  using adjMatrix = std::vector<std::vector<int64_t>>;

  static void dijkstra(const graph &G, int src, std::vector<int64_t> &dist) {
    int n = G.size();
    dist.assign(n, INF);
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
    
};

} // namespace shortest_path
} // namespace graph
