#pragma once

#include <vector>
#include <cassert>
#include <functional>

namespace hy {
namespace graph {

/**
 * @brief 匈牙利算法 (hungarian algorithm) 求二分图最大匹配
 *        
 *        简介: 
 *            https://www.renfei.org/blog/bipartite-matching.html
 *        
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P3386
 *        
 *        Time Complexity: O(m * n)
 * 
 */
int hungarian(const std::vector<std::vector<int>> &G, int n, std::vector<int> &match, int m) {
  assert(int(G.size()) >= n);
  std::vector<bool> vis(m);
  match.assign(m, 0);

  std::function<bool(int)> dfs = [&] (int u) {
    for (auto v : G[u]) if (!vis[v]) {
      if (!match[v] || dfs(match[v])) {
        match[v] = u;
        return true;
      }
    }
    return false;
  };
  
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    fill(vis.begin(), vis.end(), 0);
    if (dfs(i)) cnt++;
  }
  return cnt;
}

} // namespace graph
} // namespace hy