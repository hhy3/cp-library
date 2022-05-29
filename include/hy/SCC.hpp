#pragma once

#include <vector>
#include <queue>

namespace hy {
namespace graph {

struct SCC {
  using graph = std::vector<std::vector<int>>;
  int n, scc_num = 0;
  graph& G;
  graph S;
  std::vector<int> id, topo;
  std::vector<std::vector<int>> components;
  SCC(graph& G): n((int)G.size()), G(G), id(n, -1) {
    std::vector<bool> vis(n);
    std::vector<int> post;
    for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i, G, vis, post);
    graph rG(n);
    for (int i = 0; i < n; ++i) for (auto v : G[i]) rG[v].push_back(i);
    for (int i = n-1; i >= 0; --i) if (id[post[i]] == -1) {
      components.push_back({});
      dfs2(post[i], rG, scc_num);
      scc_num++;
    }
    S.resize(scc_num);
    std::vector<int> deg(scc_num);
    for (int i = 0; i < n; ++i) for (auto v : G[i]) {
      if (int x = id[i], y = id[v]; x != y) S[x].push_back(y), deg[y]++;
    }
    std::queue<int> q;
    topo.reserve(scc_num);
    for (int i = 0; i < scc_num; ++i) if (!deg[i]) q.push(i); 
    while (q.size()) {
      int u = q.front(); q.pop();
      topo.push_back(u);
      for (auto v : S[u]) if (--deg[v] == 0) q.push(v);
    }
  }

  void dfs1(int u, graph& G, std::vector<bool>& vis, std::vector<int>& post) {
    vis[u] = true;
    for (auto v : G[u]) if (!vis[v]) dfs1(v, G, vis, post);
    post.push_back(u);
  }

  void dfs2(int u, graph& rG, int idx) {
    id[u] = idx;
    components[idx].push_back(u);
    for (auto v : rG[u]) if (id[v] == -1) dfs2(v, rG, idx);
  }
};
  

} /* graph */
} /* hy  */ 
