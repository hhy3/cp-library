#pragma once

#include <algorithm>
#include <map>
#include <numeric>
#include <vector>

namespace hy {

template <typename T = int64_t> struct Discretizer {
  std::map<T, int> mp;
  int sz = 0;

  explicit Discretizer(const std::vector<T> &v)
      : Discretizer(v.begin(), v.end()) {}

  template <typename Iter> Discretizer(Iter first, Iter last) {
    for (auto it = first; it != last; ++it) {
      mp[*it];
    }
    for (auto &[_, v] : mp) {
      v = sz++;
    }
  }

  int operator()(T x) { return mp[x]; }

  int size() { return sz; }
};

} // namespace hy