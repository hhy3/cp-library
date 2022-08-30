#pragma once

#include <cstdint>

namespace hy {
namespace misc {

struct GrayCode {
  static int64_t g(int64_t n) {
    return n ^ (n >> 1);
  }
  static int64_t inv_g(int64_t g) {
    int64_t n = 0;
    for (; g; g >>= 1) n ^= g;
    return n;
  }
};

}
}
