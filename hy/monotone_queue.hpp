#pragma once

#include <vector>
#include <deque>

namespace hy {
namespace ds {

template <typename T>
struct MonotoneQueue {
  using binary_op = function<bool(T, T)>;
  binary_op pred;
  // Sliding window maximum: auto pred = [] (T x, T y) { return x > y; } 
  // Sliding window mimimum: auto pred = [] (T x, T y) { return x < y; } 
  int window;
  std::deque<std::pair<int, T>> q;
  MonotoneQueue(binary_op pred_, int window_): pred(pred_), window(window_) {} 
  int insert(int idx, T val) { // Loop invariant: pred(q[i].second, q[i+1].second) = true
    while (q.size() && q.front().first <= idx - window) q.pop_front();
    while (q.size() && !pred(q.back().second, val)) q.pop_back();
    q.emplace_back(idx, val);
    return q.front().first;
  }
};

}
}
