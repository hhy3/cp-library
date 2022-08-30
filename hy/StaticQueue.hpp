#pragma once

#include <vector>

namespace hy {
namespace ds {

template <typename T>
struct StaticQueue {
  std::vector<T> buf;
  int head, tail;
  StaticQueue(int cap): buf(cap), head(0), tail(0) {}
  int size() { return tail - head; }
  void push(const T& x) { buf[tail++] = x; }
  T pop() { return buf[head++]; }
  T& front() { return buf[head]; }
  void clear() { head = tail = 0; }
};

}  // namespace ds
}  // namespace hy