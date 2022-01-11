#pragma once

#include <vector>


int hungarian(const vector<vector<int>> &G, int n, vector<int> &match, int m, bool one_indexed=true) {
  int offset = int(one_indexed);
  assert(G.size() >= n + offset);
  vector<bool> vis(m + offset);
  match = vector<int>(m + offset, 0);
  
  function<bool(int)> dfs = [&] (int u) {
    for (auto v : G[u]) if (!vis[v]) {
      if (!match[v] || dfs(match[v])) {
        match[v] = u;
        return true;
      }
    }
    return false;
  };
  
  int cnt = 0;
  for (int i = offset; i < n + offset; ++i) {
    fill(vis.begin(), vis.end(), 0);
    if (dfs(i)) cnt++;
  }
  return cnt;
}