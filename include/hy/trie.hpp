#pragma once

#include <vector>
#include <unordered_map>
#include <string_view>

namespace hy {
namespace ds {

/**
 * @brief 前缀树 (Trie)
 *        
 *        简介:
 *            https://oi-wiki.org/string/trie/
 *        
 *        模板题:
 *            https://leetcode-cn.com/problems/implement-trie-prefix-tree/
 *            https://leetcode-cn.com/problems/implement-trie-ii-prefix-tree/
 * 
 *        练习题： 
 *            https://www.luogu.com.cn/problem/P2580
 *            https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/
 *            https://leetcode-cn.com/problems/maximum-xor-with-an-element-from-array/
 * 
 */
template <typename T=char, int N=1024*1024>
struct trie {

  struct node {
    int word_count = 0;
    int prefix_count = 0;
    std::unordered_map<T, int> nxt;
    node() {}
  };

  std::vector<node> nodes = {node()};

  trie() {
    nodes.reserve(N);
  }

  int get(int u, const T& x) {
    if (nodes[u].nxt.count(x)) {
      return nodes[u].nxt[x];
    } else {
      return 0;
    }
  }

  int set(int u, const T& x) {
    if (nodes[u].nxt.count(x)) {
      return 0;
    }
    nodes[u].nxt[x] = nodes.size();
    nodes.push_back(node());
    return nodes[u].nxt[x];
  }

  template <typename Iter>
  void insert(Iter first, Iter last) {
    int u = 0;
    for (; first != last; first++) {
      if (!get(u, *first)) {
        set(u, *first);
      }
      u = get(u, *first);
      nodes[u].prefix_count++;
    }
    nodes[u].word_count++;
  }

  void insert(std::string_view s) {
    insert(s.begin(), s.end());
  }

  template <typename Iter> 
  bool erase(Iter first, Iter last) {
    int u = 0;
    for (; first != last; first++) {
      if (!get(u, *first)) {
        return false;
      }
      u = get(u, *first);
      if (nodes[u].prefix_count > 0) {
        nodes[u].prefix_count--;
      }
    }
    if (nodes[u].word_count > 0) {
      nodes[u].word_count--;
      return true;
    }
    return false;
  }

  bool erase(std::string_view s) {
    return erase(s.begin(), s.end());
  }

  template <typename Iter> 
  int count(Iter first, Iter last) {
    int u = 0;
    if (!advance(u, first, last)) {
      return 0;
    }
    return nodes[u].word_count;
  }

  int count(std::string_view s) {
    return count(s.begin(), s.end());
  }

  template <typename Iter> 
  bool startswith(Iter first, Iter last) {
    int u = 0;
    return advance(u, first, last);
  }

  bool startswith(std::string_view s) {
    return startswith(s.begin(), s.end());
  }

  template <typename Iter>
  int count_startswith(Iter first, Iter last) {
    int u = 0;
    if (!advance(u, first, last)) {
      return 0;
    }
    return nodes[u].prefix_count;
  }

  int count_startswith(std::string_view s) {
    return count_startswith(s.begin(), s.end());
  }

  template <typename Iter> 
  bool advance(int& u, Iter first, Iter last) {
    for (; first != last; first++) {
      if (u = get(u, *first); u == 0) {
        return false;
      }
    }
    return true;
  }

  void clear() {
    nodes.resize(1);
  }

};

} // namespace ds
} // namespace hy