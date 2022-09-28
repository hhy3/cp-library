#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

namespace hy {

template <typename T=int64_t>
struct Discretizer {
  std::map<T, int> mp;
  int sz = 0;
  template <typename Iter> Discretizer(Iter first, Iter last) {
    for (auto it = first; it != last; ++it) mp[*it];
    for (auto& [k, v] : mp) v = ++sz;
  }
  int operator [] (T x) { return mp[x]; }
};

}