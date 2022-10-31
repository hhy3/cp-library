#pragma once

#include <cstdint>
#include <vector>

namespace hy {

struct LinearBases {
  int dim, sz = 0;
  std::vector<uint64_t> B;

  explicit LinearBases(int dim_ = 31) : dim(dim), B(dim) {}

  bool insert(uint64_t x) {
    for (int i = dim - 1; i >= 0; --i)
      if (x >> i & 1) {
        if (B[i]) {
          x ^= B[i];
        } else {
          return B[i] = x, sz++, true;
        }
      }
    return false;
  }

  bool query(uint64_t x) {
    for (int i = dim - 1; i >= 0; --i) {
      if (x >> i & 1) {
        x ^= B[i];
      }
    }
    return x == 0;
  }

  uint64_t xor_max() {
    uint64_t ans = 0;
    for (int i = dim - 1; i >= 0; --i) {
      if (B[i] && (ans >> i & 1) == 0) {
        ans ^= B[i];
      }
    }
    return ans;
  }
};

} // namespace hy
