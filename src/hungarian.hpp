#pragma once

#include <vector>

/**
 * @brief 匈牙利算法 (hungarian algorithm) 求二分图最大匹配
 *        简介: https://www.renfei.org/blog/bipartite-matching.html
 *        模板题: https://www.luogu.com.cn/problem/P3386
 * 
 * @param G 
 * @param n 
 * @param match 
 * @param m 
 * @param one_indexed 
 * @return int 
 */
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