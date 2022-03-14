#include <vector>
#include <random>
#include <limits>

#include "gtest/gtest.h"
#include "hy/bigint.hpp"

using hy::math::bigint;

TEST(BigintTest, TestInitByArith) {
  bigint x {123}, y {0}, z {9876543210};
  EXPECT_EQ(x.dat, (std::vector<int>{3, 2, 1})); 
  EXPECT_EQ(y.dat, (std::vector<int>{})); 
  EXPECT_EQ(z.dat, (std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})); 
}

TEST(BigintTest, TestInitByStr) {
  bigint x {"123"}, y {"0"}, z {"9876543210"};
  EXPECT_EQ(x.dat, (std::vector<int>{3, 2, 1})); 
  EXPECT_EQ(y.dat, (std::vector<int>{})); 
  EXPECT_EQ(z.dat, (std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})); 
}

TEST(BigintTest, TestInitByVec) {
  bigint x {std::vector<int>{1, 2, 3}}, 
                   y {std::vector<int>{0}}, 
                   z {std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
  EXPECT_EQ(x.dat, (std::vector<int>{1, 2, 3})); 
  EXPECT_EQ(y.dat, (std::vector<int>{})); 
  EXPECT_EQ(z.dat, (std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})); 
}

TEST(BigintTest, TestCopy) {
  bigint x {123}, y {1234};
  auto z {x};
  EXPECT_EQ(x, z);
  z = y;
  EXPECT_EQ(y, z);
  z = z;
  EXPECT_EQ(y, z);
}

TEST(BigintTest, TestMove) {
  bigint x {123}, y {1234};
  auto z(std::move(x));
  EXPECT_EQ(z, 123);
  x = std::move(y);
  EXPECT_EQ(x, 1234);
  x = std::move(x);
  EXPECT_EQ(x, 1234);
}

TEST(BigintTest, TestToString) {
  bigint x {123}, y {1234}, z {0};
  EXPECT_EQ(to_string(x), "123");
  EXPECT_EQ(to_string(y), "1234");
  EXPECT_EQ(to_string(z), "0");
}

TEST(BigintTest, TestAdd) {
  std::mt19937 rng;
  std::uniform_int_distribution distrib;
  constexpr int iter = 10000;
  for (int i = 0; i < iter; ++i) {
    int64_t x = distrib(rng), y = distrib(rng);
    EXPECT_EQ(bigint(x) + bigint(y), x + y);
    EXPECT_EQ(bigint(x) += bigint(y), x + y);
  }
}

TEST(BigintTest, TestMul) {
  std::mt19937 rng;
  std::uniform_int_distribution distrib;
  constexpr int iter = 10000;
  for (int i = 0; i < iter; ++i) {
    int64_t x = distrib(rng), y = distrib(rng);
    EXPECT_EQ(bigint(x) * bigint(y), x * y);
  }
}

TEST(BigintTest, TestSub) {
  std::mt19937 rng;
  std::uniform_int_distribution distrib;
  constexpr int iter = 10000;
  for (int i = 0; i < iter; ++i) {
    int64_t x = distrib(rng), y = distrib(rng);
    if (x >= y) {
      EXPECT_EQ(bigint(x) - bigint(y), x - y);
      EXPECT_EQ(bigint(x) -= bigint(y), x - y);
    } 
  }
}

TEST(BigintTest, TestIneq) {
  bigint x {123}, y {"321"}, z {std::vector<int>{1, 2, 3}}, t {0};
  EXPECT_TRUE(x < y);
  EXPECT_TRUE(y == z);
  EXPECT_TRUE(z > x);
  EXPECT_TRUE(x != t);
}





