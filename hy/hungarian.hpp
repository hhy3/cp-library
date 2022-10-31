#pragma once

#include <vector>
#include <cassert>
#include <functional>

namespace hy {

int Hungarian(const std::vector<std::vector<int>> &G, std::vector<int> &match, int m) {
  int n = G.size();
  std::vector<bool> vis(m);
  match.assign(m, -1);
  std::function<bool(int)> dfs = [&] (int u) {
    for (auto v : G[u]) if (!vis[v]) {
      if (match[v] == -1 || dfs(match[v])) {
        match[v] = u;
        return true;
      }
    }
    return false;
  };
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    fill(vis.begin(), vis.end(), false);
    if (dfs(i)) cnt++;
  }
  return cnt;
}

} // namespace hy
