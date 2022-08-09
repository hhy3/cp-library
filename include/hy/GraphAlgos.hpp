#pragma once

#include <vector>
#include <queue>

namespace hy {
namespace graph {

std::vector<int> TopoSort(const std::vector<std::vector<int>>& G, int n) {
  std::vector<int> deg(n), topo;
  topo.reserve(n);
  std::queue<int> q;
  for (int u = 0; u < n; ++u) for (auto v : G[u]) deg[v]++;
  for (int u = 0; u < n; ++u) if (!deg[u]) q.push(u);
  while (q.size()) {
    int u = q.front(); q.pop();
    topo.push_back(u);
    for (auto v : G[u]) if (--deg[v] == 0) q.push(v);
  }
  return topo;
}

}  // namespace graph
}  // namespace hy