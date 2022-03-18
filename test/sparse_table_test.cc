#include <vector>

#include "gtest/gtest.h"
#include "hy/sparse_table.hpp"

TEST(SparseTableTest, Test) {
  sparse_table<int> st(std::vector<int> {9, 3, 1, 7, 5, 6, 0, 8},
                  [](int x, int y) { return std::max(x, y); });
  EXPECT_EQ(st.query(0, 5), 9);
  EXPECT_EQ(st.query(0, 4), 9);
  EXPECT_EQ(st.query(1, 6), 7);
  EXPECT_EQ(st.query(1, 5), 7);
  EXPECT_EQ(st.query(0, 7), 9);
  EXPECT_EQ(st.query(3, 7), 8);
  EXPECT_EQ(st.query(2, 6), 7);
  EXPECT_EQ(st.query(0, 7), 9);
}