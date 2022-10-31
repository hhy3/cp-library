#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <vector>

namespace hy {

template <typename T> struct MonotoneStackPred {
  bool operator()(const T &x, const T &y) {
    // Nearest greater: return x > y;
    // Nearest smaller: return x < y;
    return x < y;
  }
};

template <typename T = std::int32_t, typename Pred = MonotoneStackPred<T>>
struct MonotoneStack {
  Pred pred;
  int id; // default index
  MonotoneStack(int id_ = -1) : id(id_) {}
  std::vector<std::pair<int, T>> stk;
  int insert(int idx, T val) {
    while (stk.size() && !pred(stk.back().second, val)) {
      stk.pop_back();
    }
    // Loop invariant: pred(stk[i].second, stk[i+1].second) = true
    int ans = stk.empty() ? id : stk.back().first;
    stk.emplace_back(idx, val);
    return ans;
  }
};

} // namespace hy