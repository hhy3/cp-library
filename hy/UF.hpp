#pragma once

#include <vector>
#include <map>
#include <numeric>

namespace hy {
namespace ds {

struct UF {
  struct node { int p, sz; };
  int n, num_component;
  std::vector<node> nodes;
  explicit UF(int n_): n(n_), num_component(n), nodes(n) {
    for (int i = 0; i < n; ++i) nodes[i].p = i, nodes[i].sz = 1;
  } 
  node& operator [] (int i) { return nodes[i]; }
  int find(int u) { return nodes[u].p == u? u : nodes[u].p = find(nodes[u].p); }
  bool is_connected(int u, int v) { return find(u) == find(v); }
  bool merge(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return false;
    if (nodes[pu].sz > nodes[pv].sz) std::swap(pu, pv);
    nodes[pu].p = pv, nodes[pv].sz += nodes[pu].sz, num_component--;
    return true;
  }
  int size(int u) { return nodes[find(u)].sz; }
  std::vector<int> leaders() {
    std::vector<int> ans;
    for (int i = 0; i < n; ++i) if (find(i) == i) ans.push_back(i);
    return ans;
  }
  std::map<int, std::vector<int>> components() {
    std::map<int, std::vector<int>> mp;
    for (int i = 0; i < n; ++i) mp[find(i)].push_back(i);
    return mp;
  }
};

} // namespace ds
} // namespace hy



