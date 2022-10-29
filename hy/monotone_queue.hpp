#pragma once

#include <cstdint>
#include <deque>
#include <functional>
#include <vector>

namespace hy {

template <typename T = std::int32_t,
          typename BinaryOp =
              decltype([](const T &x, const T &y) { return x < y; })>
struct MonotoneQueue {
  BinaryOp pred;
  // Sliding window maximum: auto pred = [] (T x, T y) { return x > y; }
  // Sliding window mimimum: auto pred = [] (T x, T y) { return x < y; }
  std::deque<std::pair<int, T>> q;
  int window;
  explicit MonotoneQueue(int window_) : window(window_) {}
  // Loop invariant: pred(q[i].second, q[i+1].second) = true
  int insert(int idx, const T &x) {
    while (q.size() && q.front().first <= idx - window) {
      q.pop_front();
    }
    while (q.size() && !pred(q.back().second, x)) {
      q.pop_back();
    }
    q.emplace_back(idx, x);
    return q.front().first;
  }
};

} // namespace hy
