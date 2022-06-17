#pragma once

#include <vector>
#include <map>
#include <cstdint>

namespace hy {
namespace ds {

template <typename T=char>
struct Trie {
  struct node {
    int cnt = 0, pcnt = 0;
    std::map<T, int> nxt;
    int& operator [] (T x) { return nxt[x]; } 
  };
  std::vector<node> tr = {node()};
  node& operator [] (int idx) { return tr[idx]; }

  template <typename Iter>
  void insert(Iter first, Iter last) {
    int u = 0;
    for (; first != last; first++) {
      if (!tr[u][*first]) tr[u][*first] = (int)tr.size(), tr.push_back(node());
      tr[u = tr[u][*first]].pcnt++;
    }
    tr[u].cnt++;
  }

  template <typename Iter> 
  bool erase(Iter first, Iter last) {
    if (!advance(first, last)) return false;
    int u = 0;
    for (; first != last; first++) {
      if (--tr[u][*first].pcnt == 0) {
        tr[u].erase(*first);
        return true;
      }
      u = tr[u][*first];
    }
    tr[u].cnt--;
    return true;
  }

  template <typename Iter> 
  int advance(Iter first, Iter last) {
    int u = 0;
    for (; first != last; first++) if ((u = tr[u][*first]) == 0) return u;
    return u;
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

} // namespace ds
} // namespace hy
