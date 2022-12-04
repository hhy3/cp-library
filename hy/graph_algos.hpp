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

} // namespace hy