#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstdint>

namespace hy {
namespace graph {

struct MST {
  
  using graph = std::vector<std::vector<std::pair<int, int64_t>>>;

  static std::vector<std::array<int, 2>> Kruskal(int n, std::vector<std::array<int, 3>>& edges) {
    std::sort(edges.begin(), edges.end(), [] (auto& e1, auto& e2) { return e1[2] < e2[2]; });
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::function<int(int)> find = [&] (int u) { return u == p[u]? u : p[u] = find(p[u]); };
    std::vector<std::array<int, 2>> ans;
    for (auto [u, v, w] : edges) {
      if (int pu = find(u), pv = find(v); pu != pv) p[pu] = pv, ans.push_back({u, v});
    } 
    return ans;
  }
};

}
}