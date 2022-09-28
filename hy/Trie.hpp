#pragma once

#include <vector>
#include <array>
#include <queue>
#include <string_view>
#include <cstdint>

namespace hy {

struct Trie {
  static constexpr int K = 26;
  static int ord(char c) { return c - 'a'; }
  struct node {
    int cnt = 0, fail = 0, nxt[K] {};
    int& operator [] (int idx) { return nxt[idx]; }
  };
  std::vector<node> tr = {node()};
  node& operator [] (int idx) { return tr[idx]; }
  void insert(std::string_view s) {
    int u = 0;
    for (auto c : s) {
      int x = ord(c);
      if (!tr[u][x]) tr[u][x] = (int)tr.size(), tr.push_back(node());
      u = tr[u][x];
    }
    tr[u].cnt++;
  }
  void buildAC() {
    std::queue<int> q;
    for (int j = 0; j < K; ++j) if (tr[0][j]) q.push(tr[0][j]);
    while (q.size()) {
      int u = q.front(); q.pop();
      for (int j = 0; j < K; ++j) {
        if (tr[u][j]) tr[tr[u][j]].fail = tr[tr[u].fail][j], q.push(tr[u][j]);
        else tr[u][j] = tr[tr[u].fail][j];
      } 
    }
  }
};

struct Trie01 {
  static const int MAXBITS = 30;
  std::vector<std::array<int, 2>> tr = {{0, 0}};
  void insert(uint64_t x) {
    int u = 0;
    for (int i = MAXBITS; i >= 0; --i) {
      int r = x >> i & 1;
      if (!tr[u][r]) tr[u][r] = (int)tr.size(), tr.push_back({0, 0});
      u = tr[u][r];
    }
  }
  uint64_t xor_max(uint64_t x) {
    int u = 0;
    uint64_t y = 0;
    for (int i = MAXBITS; i >= 0; --i) {
      int r = x >> i & 1;
      if (tr[u][r^1]) y = y * 2 + 1, u = tr[u][r^1];
      else y = y * 2, u = tr[u][r];
    }
    return y;
  }
  std::array<int, 2>& operator [] (int idx) { return tr[idx]; }
};

} // namespace hy
