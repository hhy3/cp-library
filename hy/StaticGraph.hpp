#pragma once

#include <algorithm>
#include <vector>
#include <numeric>

namespace hy {
namespace graph {

struct StaticGraph {
  struct Edge {
    int to;
    Edge(int to_) : to(to_) {}
  };
  int n, m;
  std::vector<int> head;
  std::vector<Edge> edges;
  std::vector<std::pair<int, Edge>> pool;
  StaticGraph(int n_, int m_) : n(n_), m(m_), head(n_ + 1), edges(m_) { pool.reserve(m_); }
  void add(int u, const Edge& e) {
    ++head[u];
    pool.emplace_back(u, e);
  }
  void add(int u, int v) { add(u, Edge(v)); }
  void build() {
    std::partial_sum(std::begin(head), std::end(head), std::begin(head));
    for (auto&& [src, e] : pool) edges[--head[src]] = std::move(e);
    pool.clear();
    for (int v = 0; v < n; ++v)
      std::sort(edges.begin() + head[v], edges.begin() + head[v + 1],
                [](auto&& a, auto&& b) { return a.to < b.to; });
  }
  template <class Func> void for_each_outedge(int v, Func&& f) const {
    std::for_each(edges.begin() + head[v], edges.begin() + head[v + 1], f);
  }
};

}  // namespace graph
}  // namespace hy