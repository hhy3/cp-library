#pragma once

#include <functional>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace hy {

inline bool is_biparitite(const std::vector<std::vector<int>>& graph) {
  int n = graph.size();
  std::vector<int> color(n, -1);
  std::function<bool(int, int)> dfs = [&](int u, int c) {
    color[u] = c;
    for (auto v : graph[u]) {
      if (color[v] == -1) {
        if (!dfs(v, c ^ 1)) {
          return false;
        }
      } else if (color[v] == c) {
        return false;
      }
    }
    return true;
  };
  for (int i = 0; i < n; ++i) {
    if (color[i] == -1) {
      if (!dfs(i, 0)) {
        return false;
      }
    }
  }
  return true;
}

struct SCC {
  using Graph = std::vector<std::vector<int>>;
  int n, scc_num = 0;
  const Graph& G;
  Graph S;
  std::vector<int> id, topo;
  std::vector<std::vector<int>> components;
  explicit SCC(const Graph& graph)
      : n((int)graph.size()), G(graph), id(n, -1) {
    std::vector<bool> vis(n);
    std::vector<int> post;
    std::function<void(int)> dfs1 = [&](int u) {
      vis[u] = true;
      for (auto v : G[u]) {
        if (!vis[v]) dfs1(v);
      }
      post.push_back(u);
    };
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) dfs1(i);
    }
    Graph rG(n);
    for (int i = 0; i < n; ++i) {
      for (auto v : G[i]) rG[v].push_back(i);
    }
    std::function<void(int, int)> dfs2 = [&](int u, int idx) {
      id[u] = idx;
      components[idx].push_back(u);
      for (auto v : rG[u]) {
        if (id[v] == -1) dfs2(v, idx);
      }
    };
    for (int i = n - 1; i >= 0; --i) {
      if (id[post[i]] == -1) {
        components.push_back({});
        dfs2(post[i], scc_num);
        scc_num++;
      }
    }
    S.resize(scc_num);
    std::vector<int> deg(scc_num);
    for (int i = 0; i < n; ++i) {
      for (auto v : G[i]) {
        if (int x = id[i], y = id[v]; x != y) {
          S[x].push_back(y);
          deg[y]++;
        }
      }
    }
    std::queue<int> q;
    topo.reserve(scc_num);
    for (int i = 0; i < scc_num; ++i) {
      if (!deg[i]) q.push(i);
    }
    while (q.size()) {
      int u = q.front();
      q.pop();
      topo.push_back(u);
      for (auto v : S[u]) {
        if (--deg[v] == 0) q.push(v);
      }
    }
  }
};

struct GraphBridges {
  int n;
  std::vector<int> tin, low;
  std::vector<std::pair<int, int>> bridges;
  explicit GraphBridges(const std::vector<std::vector<int>>& G) {
    n = G.size();
    tin.assign(n, 0);
    low.assign(n, 0);
    int timer = 0;
    std::function<void(int, int)> dfs = [&](int u, int p) {
      tin[u] = low[u] = ++timer;
      for (auto v : G[u]) {
        if (v != p) {
          if (tin[v]) {
            low[u] = std::min(low[u], tin[v]);
          } else {
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
            if (tin[u] < low[v]) {
              bridges.emplace_back(std::min(u, v), std::max(u, v));
            }
          }
        }
      }
    };
    for (int i = 0; i < n; ++i) {
      if (!tin[i]) dfs(i, -1);
    }
  }
};

struct ArticulationPoints {
  int n;
  std::vector<int> tin, low;
  std::vector<bool> is_articulation;
  std::vector<std::vector<int>> components;
  explicit ArticulationPoints(const std::vector<std::vector<int>>& G) {
    n = G.size();
    tin.assign(n, 0);
    low.assign(n, 0);
    is_articulation.assign(n, false);
    int timer = 0;
    std::stack<int> stk;
    std::function<void(int, int)> dfs = [&](int u, int p) {
      tin[u] = low[u] = ++timer;
      stk.push(u);
      if (p == -1 && G[u].empty()) {
        components.push_back({u});
        return;
      }
      int cnt = 0;
      for (auto v : G[u]) {
        if (tin[v] > 0) {
          low[u] = std::min(low[u], tin[v]);
        } else {
          dfs(v, u);
          low[u] = std::min(low[u], low[v]);
          if (tin[u] <= low[v]) {
            cnt++;
            if (p != -1 || cnt > 1) {
              is_articulation[u] = true;
            }
            std::vector<int> component;
            do {
              component.push_back(stk.top());
              stk.pop();
            } while (component.back() != v);
            component.push_back(u);
            components.push_back(component);
          }
        }
      }
    };
    for (int i = 0; i < n; ++i) {
      if (tin[i] == 0) {
        dfs(i, -1);
      }
    }
  }
};

// Reference: https://judge.yosupo.jp/submission/66608
struct DominatorTree {
  std::vector<std::basic_string<int>> g, rg, bucket;
  std::basic_string<int> arr, par, rev, sdom, dom, dsu, label;
  int n, t;
  DominatorTree(int n)
      : g(n),
        rg(n),
        bucket(n),
        arr(n, -1),
        par(n, -1),
        rev(n, -1),
        sdom(n, -1),
        dom(n, -1),
        dsu(n, 0),
        label(n, 0),
        n(n),
        t(0) {}
  void add_edge(int u, int v) { g[u] += v; }
  void dfs(int u) {
    arr[u] = t;
    rev[t] = u;
    label[t] = sdom[t] = dsu[t] = t;
    t++;
    for (int w : g[u]) {
      if (arr[w] == -1) {
        dfs(w);
        par[arr[w]] = arr[u];
      }
      rg[arr[w]] += arr[u];
    }
  }
  int find(int u, int x = 0) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = find(dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  }
  std::vector<int> run(int root) {
    dfs(root);
    std::iota(dom.begin(), dom.end(), 0);
    for (int i = t - 1; i >= 0; i--) {
      for (int w : rg[i]) sdom[i] = std::min(sdom[i], sdom[find(w)]);
      if (i) bucket[sdom[i]] += i;
      for (int w : bucket[i]) {
        int v = find(w);
        if (sdom[v] == sdom[w])
          dom[w] = sdom[w];
        else
          dom[w] = v;
      }
      if (i > 1) dsu[i] = par[i];
    }
    for (int i = 1; i < t; i++) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    }
    std::vector<int> outside_dom(n, -1);
    for (int i = 1; i < t; i++) outside_dom[rev[i]] = rev[dom[i]];
    return outside_dom;
  }
};

}  // namespace hy