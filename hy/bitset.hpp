#pragma once

#include <cstdlib>
#include <memory>

namespace hy {

struct Bitset {
  std::unique_ptr<uint64_t[]> data;

  Bitset(int n) : data(std::make_unique<uint64_t[]>((n + 63) / 64)) {}

  bool get(int i) { return uint64_t(1) & (data[i >> 6] >> (i & 63)); }

  void set(int i) { data[i >> 6] |= (uint64_t(1) << (i & 63)); }

  void clear(int i) { data[i >> 6] &= ~((uint64_t(1) << (i & 63))); }
};

} // namespace hy