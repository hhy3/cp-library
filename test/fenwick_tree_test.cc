#include "gtest/gtest.h"
#include "hy/fenwick_tree.hpp"


TEST(FenwickTreeTest, SinglePointUpdate) {
  hy::ds::fenwick_tree<int> ft(5);
  for (int i = 1; i <= 5; ++i) {
    ft.update(i, i);
  }
  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(ft.query(i, i), i);
  }
}

TEST(FenwickTreeTest, RangeUpdate) {
  hy::ds::fenwick_tree<int> ft(5, true);
  ft.update(1, 3, 2);
  ft.update(2, 4, 3);
  EXPECT_EQ(ft.query(1, 4), 15);
  ft.update(2, 5, -1);
  EXPECT_EQ(ft.query(3, 5), 5);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}