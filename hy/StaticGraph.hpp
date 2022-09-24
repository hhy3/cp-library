#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace hy {
namespace graph {

namespace StaticGraph {
// Modify these two lines if needed;
constexpr int N = 1e6 + 10;
constexpr int M = 1e6 + 10;

int head[N], edge[M], next[M], tot = 0;

void add(int u, int v) {
  tot++;
  edge[tot] = v, next[tot] = head[u], head[u] = tot;
}

// iterate adj list of point u:
//   for (int i = head[u]; i; i = next[i]) {
//     int v = edge[i];
//   }

}  // namespace StaticGraph

}  // namespace graph
}  // namespace hy