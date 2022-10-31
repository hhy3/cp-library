#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <numeric>
#include <vector>

#include "uf.hpp"

namespace hy {

struct MST {
  int n;
  std::vector<std::array<int64_t, 3>> edges;
  std::vector<std::array<int64_t, 2>> tree;
  UF uf;
  int64_t cost = 0;
  bool connected = false;
  MST(int n, int m) : n(n), uf(n) { edges.reserve(m); }
  void add_edge(int u, int v, int64_t w) { edges.push_back({u, v, w}); }
  void Kruskal() {
    std::sort(edges.begin(), edges.end(),
              [](auto &lhs, auto &rhs) { return lhs[2] < rhs[2]; });
    for (auto [u, v, w] : edges) {
      if (uf.merge(u, v)) {
        cost += w;
        tree.push_back({u, v});
      }
    }
    if (uf.num_component == 1) {
      connected = true;
    }
  }
};

} // namespace hy