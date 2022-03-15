#include <vector>

#include "gtest/gtest.h"
#include "hy/fft.hpp"

using hy::math::convolution;

TEST(FFTTest, TestConvolution) {
  std::vector<int64_t> a {1, 2}, b {1, 2, 1}, c {1, 4, 5, 2};
  auto conv = convolution(a, b);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(conv[i], c[i]);
  }
}