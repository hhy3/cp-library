#pragma once

#include <map>
#include <vector>

namespace hy {

template <typename T = int> struct PersistentStack {
  std::vector<std::vector<int>> G;
  std::vector<int> p;
  std::vector<T> a;
  std::map<int, int> mp;
  int cur = 0;
  PersistentStack() : G(1), p(1), a(1, -1) {}
  void push(const T &x) {
    p.push_back(cur);
    G.emplace_back();
    G[cur].push_back(p.size() - 1);
    a.push_back(x);
    cur = p.size() - 1;
  }
  void pop() { cur = p[cur]; }
  T &back() { return a[cur]; }
  void save(int version) { mp[version] = cur; }
  void load(int version) { cur = mp[version]; }
};

} // namespace hy