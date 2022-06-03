#pragma once

#include <vector>

namespace hy {
namespace graph {

struct TransitiveClosure {
  int n;
  std::vector<std::vector<bool>> adj;
  TransitiveClosure(int n): n(n), adj(n, std::vector<bool>(n)) {} 
  void add_edge(int u, int v) { adj[u][v] = true;}
  void build() {
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
      if (adj[i][k] && adj[k][j]) adj[i][j] = true;
  }
  bool is_connect(int u, int v) { return adj[u][v]; }
};

}
}
