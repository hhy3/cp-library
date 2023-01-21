#pragma once

#include <queue>
#include <vector>
#include <cassert>

namespace hy {

struct TopoSorter {
  int n;
  std::vector<std::vector<int>> G;
  std::vector<int> topo, deg;
  bool prepared = false; 
  TopoSorter(int num) : n(num), G(n), deg(n) { topo.reserve(n); }
  void add_edge(int u, int v) { G[u].push_back(v), deg[v]++; }
  void build() {
    std::queue<int> q;
    for (int u = 0; u < n; ++u) if (!deg[u]) q.push(u);
    while (q.size()) {
      int u = q.front();
      q.pop();
      topo.push_back(u);
      for (auto v : G[u]) if (--deg[v] == 0) q.push(v);
    }
    prepared = true;
  }
  bool is_dag() {
    assert(prepared);
    return (int)topo.size() == n;
  }
  int operator[](int idx) {
    assert(idx < n);
    return topo[idx];
  }
};

}  // namespace hy