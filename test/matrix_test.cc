#include <vector>
#include <utility>

#include "gtest/gtest.h"
#include "hy/matrix.hpp"

using hy::math::matrix;

TEST(MatrixTest, MatrixInit) {
  matrix mat1(3, 2);
  EXPECT_EQ(mat1.shape(), std::make_pair(3, 2));
  std::vector<std::vector<int>> v = {{1, 2}, {2, 3}};
  matrix mat2(v);
  EXPECT_EQ(mat2.shape().first, v.size());
  EXPECT_EQ(mat2.shape().second, v[0].size());
  for (int i = 0; i < (int)v.size(); ++i) {
    for (int j = 0; j < (int)v[0].size(); ++j) {
      EXPECT_EQ(mat2[i][j], v[i][j]);
    }
  }
  matrix mat3(mat1);
  EXPECT_EQ(mat1.shape(), mat3.shape());
  for (int i = 0; i < (int)v.size(); ++i) {
    for (int j = 0; j < (int)v[0].size(); ++j) {
      EXPECT_EQ(mat1[i][j], mat3[i][j]);
    }
  }
  matrix mat4(std::move(mat1));
  EXPECT_EQ(mat3.shape(), mat4.shape());
  for (int i = 0; i < (int)v.size(); ++i) {
    for (int j = 0; j < (int)v[0].size(); ++j) {
      EXPECT_EQ(mat3[i][j], mat4[i][j]);
    }
  }
}

TEST(MatrixTest, MatrixPow) {
  matrix mat(std::vector<std::vector<int64_t>>{{0, 1}, {1, 1}});
  int64_t x = 0, y = 1, mod = 1e9 + 7;
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(mat.modpow(i, mod)[1][0], x);
    std::tie(x, y) = std::make_pair(y, (x + y) % mod);
  }
}