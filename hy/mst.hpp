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
  struct UF {
    std::vector<int> p;
    int num_components;
    explicit UF(int n) : p(n), num_components(n) {
      std::iota(p.begin(), p.end(), 0);
    }
    int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }
    int merge(int u, int v) {
      int pu = find(u), pv = find(v);
      if (pu == pv) {
        return false;
      } else {
        num_components--;
        p[pu] = pv;
        return true;
      }
    }
  } uf;
  int64_t cost = 0;
  bool connected = false;
  MST(int n_, int m_) : n(n_), uf(n_) { edges.reserve(m_); }
  void add_edge(int u, int v, int64_t w) { edges.push_back({u, v, w}); }
  void build() {
    std::sort(edges.begin(), edges.end(),
              [](auto &lhs, auto &rhs) { return lhs[2] < rhs[2]; });
    for (auto [u, v, w] : edges) {
      if (uf.merge(u, v)) {
        cost += w;
        tree.push_back({u, v});
      }
    }
    if (uf.num_components == 1) {
      connected = true;
    }
  }
};

} // namespace hy