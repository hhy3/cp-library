#include "gtest/gtest.h"
#include "hy/segtree.hpp"


TEST(SegtreeTest, Test) {
  segtree tr(3);
  tr.update(1, 1);
  tr.update(3, 5);
  tr.update(2, 3);
  EXPECT_EQ(tr.reduce(1, 3), 9);
  tr.update(2, 2);
  EXPECT_EQ(tr.reduce(1, 3), 8);
}