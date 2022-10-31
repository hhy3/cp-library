#pragma once

#include <cstdint>
#include <deque>
#include <functional>
#include <vector>

namespace hy {

template <typename T> struct MonotoneQueuePred {
  bool operator()(const T &x, const T &y) {
    // Sliding window maximum: return x > y;
    // Sliding window mimimum: return x < y;
    return x < y;
  }
};

template <typename T = std::int32_t, typename Pred = MonotoneQueuePred<T>>
struct MonotoneQueue {
  Pred pred;
  std::deque<std::pair<int, T>> q;
  int window;
  int cnt = 0;
  explicit MonotoneQueue(int window_) : window(window_) {}
  // Loop invariant: pred(q[i].second, q[i+1].second) = true
  T insert(const T &x) {
    cnt++;
    while (q.size() && q.front().first <= cnt - window) {
      q.pop_front();
    }
    while (q.size() && !pred(q.back().second, x)) {
      q.pop_back();
    }
    q.emplace_back(cnt, x);
    return q.front().second;
  }
};

} // namespace hy
