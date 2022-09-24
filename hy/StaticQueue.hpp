#pragma once

#include <vector>

namespace hy {
namespace ds {

namespace StaticQueue {
// modify these two lines if needed.
using T = int;
constexpr int N = 1e6 + 10;

T buf[N];
int head = 0, tail = 0;
int size() { return tail - head; }
void push(const T& x) { buf[tail++] = x; }
void pop() { head++; }
T& front() { return buf[head]; }
void clear() { head = tail = 0; }

}  // namespace StaticQueue

}  // namespace ds
}  // namespace hy