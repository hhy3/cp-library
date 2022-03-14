#include <random>

#include "gtest/gtest.h"
#include "hy/modint.hpp"

using hy::math::modint;

TEST(ModintTest, TestInit) {
  EXPECT_EQ(modint<7>(-1), 6);
  EXPECT_EQ(modint<7>(8), 1);
  EXPECT_EQ(modint<7>(-3), modint<7>(11));
}

TEST(ModintTest, TestInv) {
  constexpr uint64_t mod = 1e9 + 7;
  constexpr int iter = 1000;
  std::mt19937 rng;
  std::uniform_int_distribution<int> distrib;
  for (int i = 0; i < iter; ++i) {
    modint<mod> x = distrib(rng);
    EXPECT_EQ(x.inv() * x, 1);
  }
}

TEST(ModintTest, TestDiv) {
  constexpr uint64_t mod = 1e9 + 7;
  constexpr int iter = 1000;
  std::mt19937 rng;
  std::uniform_int_distribution<int> distrib;
  for (int i = 0; i < iter; ++i) {
    modint<mod> x = distrib(rng), y = distrib(rng);
    EXPECT_EQ(x / y * y, x);
  }
}