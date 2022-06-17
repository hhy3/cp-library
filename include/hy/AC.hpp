#pragma once

#include <vector>
#include <map>
#include <map>
#include <string_view>
#include <type_traits>

#include <cassert>

namespace hy {
namespace string {

template <typename T=char, int N=1024*1024>
struct AC {
  
  struct node {
    int p = -1;
    T pch;
    int link = -1;
    int leaf = 0;
    std::map<T, int> nxt;
    std::map<T, int> go;

    node(int p, const T& pch): p(p), pch(pch) {}

  };

  std::vector<node> nodes = {node(0, T())};
  
  AC() {
    nodes.reserve(N);
  }

  template <typename Iter>
  int insert(Iter first, Iter last) {
    int u = 0;
    for (; first != last; ++first) {
      if (!nodes[u].nxt.count(*first)) {
        nodes[u].nxt[*first] = nodes.size();
        nodes.emplace_back(u, *first);
      }
      u = nodes[u].nxt[*first];
    }
    nodes[u].leaf++;
    return u;
  }

  int insert(std::string_view s) {
    assert((std::is_same_v<T, char>));
    return insert(s.begin(), s.end());
  }

  int go(int u, const T& x) {
    if (!nodes[u].go.count(x)) {
      if (nodes[u].nxt.count(x)) {
        nodes[u].go[x] = nodes[u].nxt[x];
      } else {
        nodes[u].go[x] = u? go(get_link(u), x) : 0;
      }
    }
    return nodes[u].go[x];
  }

  int get_link(int u) {
    if (nodes[u].link == -1) {
      if (u == 0 || nodes[u].p == 0) {
        nodes[u].link = 0;
      } else {
        nodes[u].link = go(get_link(nodes[u].p), nodes[u].pch);
      }
    }
    return nodes[u].link;
  }

  template <typename Iter>
  int count_pattern_in_text(Iter first, Iter last) {
    int ans = 0, u = 0;
    std::unordered_set<int> vis;
    for (; first != last; ++first) {
      u = go(u, *first);
      for (int v = u; v; v = get_link(v)) {
        if (!vis.count(v)) {
          ans += nodes[v].leaf;
          vis.insert(v);
        } else {
          break;
        }
      }
    }
    return ans;
  }

  int count_pattern_in_text(std::string_view text) {
    assert((std::is_same_v<T, char>));
    return count_pattern_in_text(text.begin(), text.end());
  }

};


} // namespace ds
} // namespace hy
